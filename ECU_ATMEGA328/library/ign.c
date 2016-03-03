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
	EIMSK |= (1 << INT1);						// Enable INT0 interrupt
	// Clock to time from crank signal to ignition pulse
	TCCR1B |= (1 << CS10) | (1 << CS11);		// Prescale to 4µs
	// Overflow interrupt for cycle less than 65536*4µs = 0,262144 s
	//TIMSK1 |= (1 << TOIE1);			// Turn on overflow interrupt
	TIMSK1 |= (1 << OCIE1B);			// Turn on compare match B interrupt
	// Initialize the counter value
	TCNT1 = 0;									// Zero counter 1
	// Declare the pin used for the DCI ignition system
	DDRD |= (1 << PIND4);						// Ignition pin
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
			{-2.0, 8.0,	8.0, 8.0, 8.0, 12.4, 18.3, 24.2, 30.0, 30.0, 30.0, 30.0,
			30.0, 30.0, 30.0, 30.0, 30.0, 30.0, 30.0, 30.0, 30.0, 26.0, 18.0};


	for(int i = 0; i < table.RPMLength; i++)
	{
		table.RPM[i] = temp_rpm[i];
		unsigned long temp = 60000000 / (temp_rpm[i] * 4) ; // in 4µs count values
		table.Cycle[i] = temp;
		table.Table[i] = temp_table[i];
	}
}

// Interrupts when low signal on crankshaft (60°BTDC)
ISR(INT1_vect)
{
	engine.rpm_c = TCNT1; 	// Store the latest cycle value
	TCNT1 = 0; 				// Initialize the cycle counter
	if (engine.rpm_c > STARTING_COUNTS)
	{
		EIMSK |= (1 << INT0);						// Enable INT0 interrupt
		return;
	}
	if(engine.rpm_c < REV_LIMIT_COUNTS)
	{
		return;
	}
	/*if (ovf == 1) {			// If the cycle was longer than 0,262 sec
		ovf = 0;			// To be implemented later !!!!!!!!!!!!!!!!!!!!
		return;
	}*/
	char lowRPMIndex = 0;
	char highRPMIndex = table.RPMLength - 1;
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
	unsigned char degree = 0;
	if (highRPMIndex == 0) { // below 500 rpm in our case
		EIMSK |= (1 << INT1);						// Enable INT1 interrupt
		engine.status = false;
		return;
	} else {
		engine.status = true;
		degree = (table.Table[highRPMIndex] + table.Table[highRPMIndex]) / 2;
	}
	uint16_t calc_counts = (engine.rpm_c / 360) * (CRANK_SIGNAL_ANGLE - degree);
	OCR1B = calc_counts - TCNT1;
	engine.ign = true;
}

ISR(TIMER1_COMPB_vect)
{
	if (engine.ign)
	{
		PORTD &= ~(1 << PIND4);			// Turn on ignition
		engine.ign = false;				// Turn flag off
		OCR1B = TCNT1 + IGN_COUNTS;		// Turn off ignition after specified time
	}
	else
	{
		PORTD |= (1 << PIND4);			// Turn off ignition
	}
}

/*ISR(TIMER1_OVF_vect)
{
	ovf = 1; 								// over flow occurred
}*/

//Crank high, 2 degrees advanced top dead center
ISR(INT0_vect)
{
	PORTD &= ~(1 << PIND4);						// Turn on ignition
	OCR1B = TCNT1 + IGN_COUNTS;					// Turn off ignition after specified time
	EIMSK &= ~(1 << INT0);						// Disable INT0 interrupt
}




