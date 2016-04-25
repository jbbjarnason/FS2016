/*
 * ign.c
 *
 *  Created on: 3. feb. 2016
 * 		 Author: JonB
 */

#include "ign.h"
#include "global.h"
#include "delay.h"

unsigned int print_counter = 0;

void initIgnition()
{
	// Initialize structs
	initIgnTable();
	engine_rpm_c = 0;
	engine_ign = true;

	cli();	// Turn global interrupts off
	// Crankshaft interrupt pins
	EICRA |= (1 << ISC11) | (1 << ISC10);		// Set INT1 to rising edge
	// Crankshaft Low signal, comes 60° before top dead center
	EIMSK |= (1 << INT1);						// Enable INT1 interrupt
	// Clock to time from crank signal to ignition pulse
	TCCR1B |= (1 << CS10) | (1 << CS11);		// Prescale to 4µs
	// Overflow interrupt for cycle less than 65536*4µs = 0,262144 s
	TIMSK1 |= (1 << TOIE1);			// Turn on overflow interrupt
	TIMSK1 |= (1 << OCIE1A) | (1 << OCIE1B); // Turn on compare match B interrupt
	// Initialize the counter value
	TCNT1 = 0;									// Zero counter 1
	OCR1A = 65535;
	OCR1B = 65535;
	// Declare the pin used for the TCI ignition system
	DDRD |= (1 << PIND4);
	PORTD &= ~(1 << PIND4);						// Turn ignition pin off
	sei(); 	// Turn global interrupts back on

}
void initIgnTable()
{
	table.RPMLength = MAINTABLE_MAX_RPM_LENGTH;
	table.LoadLength = MAINTABLE_MAX_LOAD_LENGTH;

	unsigned int temp_rpm[MAINTABLE_MAX_RPM_LENGTH] =
			{ 500,700,1100,1500,1900,2300,2700,3100,3500,3900,4300,4700,
			5100,5500,5900,6300,6700,7100,7500,7900,8300,8700,9100};

	float temp_table[MAINTABLE_MAX_RPM_LENGTH] =
			{0.0, 8.0,	8.0, 8.0, 8.0, 12.4, 18.3, 24.2, 30.0, 30.0, 30.0, 30.0,
			30.0, 30.0, 30.0, 30.0, 30.0, 30.0, 30.0, 30.0, 30.0, 26.0, 18.0}; // Byrjaði á -2 breytti 27.3.16 til að testa

	unsigned int temp_dwell[MAINTABLE_MAX_RPM_LENGTH] =
				{40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
				40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40}; // duty cycle in %, 40%

	for(int i = 0; i < table.RPMLength; i++)
	{
		table.RPM[i] = temp_rpm[i];
		unsigned long temp = 60000000 / ((long)temp_rpm[i] * 4) ; // in 4µs count values
		table.Cycle[i] = temp;
		table.Table[i] = temp_table[i];
		table.dwell[i] = temp_dwell[i]; // cycle - 40% duty cycle in counts
		print_string("RPM");print_int(temp_rpm[i]);
		print_string("CycleCounts");print_long(temp);
		print_string("DwellDutyCycle"); print_int(temp_dwell[i]);
	}
}

// Interrupts with when low signal on crankshaft (60°BTDC)
ISR(INT1_vect)										//******************
{
	engine_rpm_c = TCNT1; 	// Store the latest cycle value
	TCNT1 = 0; 				// Initialize the cycle counter

	engine_ign = (engine_rpm_c > REV_LIMIT_COUNTS);

	uint8_t lowRPMIndex = 0;
	uint8_t highRPMIndex = table.RPMLength - 1;

	for (uint8_t RPMIndex = 0; RPMIndex < table.RPMLength; RPMIndex++)
	{
		if (table.Cycle[RPMIndex] > engine_rpm_c) {
			lowRPMIndex = RPMIndex;
		} else if (table.Cycle[RPMIndex] < engine_rpm_c) {
			highRPMIndex = RPMIndex;
			break;
		} else if (table.Cycle[RPMIndex] == engine_rpm_c) {
			lowRPMIndex = RPMIndex;
			highRPMIndex = RPMIndex;
			break;
		}
	}

	unsigned char degree = ((table.Table[highRPMIndex] + table.Table[lowRPMIndex]) / 2);
	// calculate counts for compare match B to SPARK !
	uint16_t calc_counts = (engine_rpm_c / 360) * (CRANK_SIGNAL_ANGLE - degree);
	OCR1B = calc_counts; //- TCNT1;
	// calculate count for compare match A to turn on the ignition coil
	uint32_t calc_dwell = ((long)engine_rpm_c * ((table.dwell[highRPMIndex] + table.dwell[lowRPMIndex]) / 2)) / 100;
	print_counter++;
	if (OCR1B > MAX_DWELL_TIME) { // is the SPARK delay time more then maximum dwell time 9 ms ?
		OCR1A = OCR1B - MAX_DWELL_TIME;
	} else if (calc_dwell > MAX_DWELL_TIME) { // is the calculated dwell time to long ?
		OCR1A = engine_rpm_c - MAX_DWELL_TIME + OCR1B;
	} else { // use the calculated dwell time
		OCR1A = engine_rpm_c - calc_dwell + OCR1B;
	}
	//unsigned long dwell_delay = engine_rpm_c - ((4 * (long)engine_rpm_c) / 10);
	//OCR1A = (unsigned int) dwell_delay;

	/*if (print_counter > 100)
	{
		print_char('R'); print_int(engine_rpm_c);
		print_char('A'); print_int(OCR1A);
		print_char('B'); print_int(OCR1B);
		print_char('T'); print_int(TIMSK1);
		print_char('C'); print_int(TCNT1);
		print_string("low"); print_int(lowRPMIndex);
		print_string("high"); print_int(highRPMIndex);
		print_counter = 0;
	}*/
}

// Turn on coil
ISR(TIMER1_COMPA_vect)
{
	if (engine_ign)
		PORTD |= (1 << PIND4);
	else
		PORTD &= ~(1 << PIND4);
}
// Time to SPARK !!
ISR(TIMER1_COMPB_vect)
{
	PORTD &= ~(1 << PIND4); // Spark
}
// Safety for ignition overheating
ISR(TIMER1_OVF_vect)
{
	engine_ign = false;
}


