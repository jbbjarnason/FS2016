/*
 * ign.c
 *
 *  Created on: 3. feb. 2016
 * 		 Author: JonB
 */

#include "ign.h"
#include "global.h"

void ignInit()
{
	// Initialize structs
	ign_tab_init();
	engine.rpm_c = 0;
	engine.status = false;
	engine.ign = false;

	cli();	// Turn global interrupts off
	// Crankshaft interrupt pins
	EICRA |= (1 << ISC11) | (1 << ISC10);		// Set INT1 to rising edge
	EICRA |= (1 << ISC01) | (1 << ISC00);		// Set INT0 to rising edge
	// Crankshaft Low signal, comes 60° before top dead center
	EIMSK |= (1 << INT1);						// Enable INT0 interrupt*****************
	// Clock to time from crank signal to ignition pulse
	TCCR1B |= (1 << CS10) | (1 << CS11);		// Prescale to 4µs
	// Overflow interrupt for cycle less than 65536*4µs = 0,262144 s
	TIMSK1 |= (1 << TOIE1);			// Turn on overflow interrupt
	//TIMSK1 |= (1 << TOIE1);			// Turn on compare match B interrupt
	// Initialize the counter value
	TCNT1 = 0;									// Zero counter 1
	// Declare the pin used for the DCI ignition system
	DDRD |= (1 << PIND4) | (1 << PIND5);						// Ignition pin
	PORTD &= ~(1 << PIND5);
	PORTD &= ~(1 << PIND4);						// Turn ignition pin off
	sei(); 	// Turn global interrupts back on

}
void ign_tab_init()
{
	table.RPMLength = MAINTABLE_MAX_RPM_LENGTH;
	table.LoadLength = MAINTABLE_MAX_LOAD_LENGTH;

	int temp_rpm[MAINTABLE_MAX_RPM_LENGTH] =
			{ 500,700,1100,1500,1900,2300,2700,3100,3500,3900,4300,4700,
			5100,5500,5900,6300,6700,7100,7500,7900,8300,8700,9100};

	float temp_table[MAINTABLE_MAX_RPM_LENGTH] =
			{0.0, 8.0,	8.0, 8.0, 8.0, 12.4, 18.3, 24.2, 30.0, 30.0, 30.0, 30.0,
			30.0, 30.0, 30.0, 30.0, 30.0, 30.0, 30.0, 30.0, 30.0, 26.0, 18.0}; // Byrjaði á -2 breytti 27.3.16 til að testa

	unsigned int temp_dwell[MAINTABLE_MAX_RPM_LENGTH] =
				{2250, 2250, 2250, 2250, 2250, 2250, 2222, 1935, 1714, 1538, 1395, 1276,
				1176, 1090, 1016, 952, 895, 845, 800, 759, 722, 689, 659}; // Counts (4µs) 40% duty cycle but max 9 ms

	for(int i = 0; i < table.RPMLength; i++)
	{
		table.RPM[i] = temp_rpm[i];
		unsigned long temp = 60000000 / (temp_rpm[i] * 4) ; // in 4µs count values
		table.Cycle[i] = temp;
		table.Table[i] = temp_table[i];
		table.dwell[i] = temp - temp_dwell[i]; // cycle - 40% duty cycle in counts
	}
}

// Interrupts with when low signal on crankshaft (60°BTDC)
ISR(INT1_vect)										//******************
{
	PORTD |= (1 << PIND5);
	engine.rpm_c = TCNT1; 	// Store the latest cycle value
	TCNT1 = 0; 				// Initialize the cycle counter
	//println(engine.rpm_c);
	//println(STARTING_COUNTS);
	//println(REV_LIMIT_COUNTS);
	/*if(engine.rpm_c > STARTING_COUNTS)
	{
		//printchar('p');
		EIMSK |= (1 << INT0);						// Enable INT0 interrupt**************
		return;
	}*/
	if(engine.rpm_c < REV_LIMIT_COUNTS)
	{
		//println(REV_LIMIT_COUNTS);
		return;
	}
	/*if (ovf == 1) {			// If the cycle was longer than 0,262 sec
		ovf = 0;			// To be implemented later !!!!!!!!!!!!!!!!!!!!
		return;
	}*/
	uint8_t lowRPMIndex = 0;
	uint8_t highRPMIndex = table.RPMLength - 1;
	for (unsigned char RPMIndex = 0; RPMIndex < table.RPMLength; RPMIndex++)
	{
		if (table.Cycle[RPMIndex] > engine.rpm_c) {
			lowRPMIndex = RPMIndex;
		} else if (table.Cycle[RPMIndex] < engine.rpm_c) {
			highRPMIndex = RPMIndex;
			break;
		} else if (table.Cycle[RPMIndex] == engine.rpm_c) {
			lowRPMIndex = RPMIndex;
			highRPMIndex = RPMIndex;
			break;
		}
	}
	/*unsigned char degree = 0;
	if (highRPMIndex == 0) { 						// below 500 rpm in our case
		EIMSK |= (1 << INT1);						// Enable INT1 interrupt*************
		engine.status = false;
		return;
	} else {
		engine.status = true;
		degree = (table.Table[highRPMIndex] + table.Table[highRPMIndex]) / 2;
	}*/
	unsigned char degree = ((table.Table[highRPMIndex] + table.Table[lowRPMIndex]) / 2);
	uint16_t calc_counts = (engine.rpm_c / 360) * (CRANK_SIGNAL_ANGLE - degree);
	TIMSK1 |= (1 << OCIE1A) | (1 << OCIE1B);
	OCR1B = calc_counts - TCNT1;
	OCR1A = (table.dwell[highRPMIndex] + table.dwell[highRPMIndex]) / 2;
	//printchar('B');println(OCR1B);
	//println(TCNT1);
	//engine.ign = true;
	PORTD &= ~(1 << PIND5);
}


/*ISR(TIMER1_COMPB_vect)
{
	if (engine.ign)
	{
		PORTD |= (1 << PIND4);
		engine.ign = false;
		OCR1B = TCNT1 + IGN_COUNTS;
	}
	else
	{
		PORTD &= ~(1 << PIND4);
	}
}*/
// Time to turn on the ignition
ISR(TIMER1_COMPA_vect)
{
	PORTD |= (1 << PIND4); // Turn on coil
	TIMSK1 &= ~(1 << OCIE1A);
}
// Time to SPARK !!
ISR(TIMER1_COMPB_vect)
{
	PORTD &= ~(1 << PIND4); // Spark
	TIMSK1 &= ~(1 << OCIE1B);
}
ISR(TIMER1_OVF_vect)
{
	PORTD &= ~(1 << PIND4); // Safety for ignition overheating
}
/*ISR(TIMER1_OVF_vect)
{
	ovf = 1; 								// over flow occurred
}*/

//Crank high
/*ISR(INT0_vect)									//************
{
	/*PORTD |= (1 << PIND4);						// Turn on ignition
	OCR1B = TCNT1 + IGN_TIME;					// Turn off ignition after specified time
	engine.ign = false;*
	PORTD |= (1 << PIND4);
	OCR1B = TCNT1 + IGN_COUNTS;
	EIMSK &= ~(1 << INT0);						// Disable INT0 interrupt**********
}
*/



