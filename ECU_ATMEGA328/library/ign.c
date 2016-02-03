/*
 * ign.c
 *
 *  Created on: 3. feb. 2016
 *      Author: JonB
 */

#include "ign.h"


void ignInit()
{
	cli();	// Turn interrupts off
	// Crankshaft interrupt pins
	EICRA |= (1 << ISC11) | (1 << ISC10);		// Set INT1 to rising edge
	EICRA |= (1 << ISC01) | (1 << ISC00);		// Set INT0 to rising edge
	// Crankshaft Low signal, comes 60° before top dead center
	EIMSK |= (1 << INT0);						// Enable INT0 interrupt
	// Clock to time from crank signal to ignition pulse
	TCCR1B |= (1 << CS10) | (1 << CS11);		// Prescale to 4µs
	// Overflow interrupt for cycle less than 65536*4µs = 0,262144 s
	TIMSK1 |= (1 << TOIE1);				// Turn on overflow interrupt
	// Initialize the counter value
	TCNT1 = 0;									// Zero counter 1
	// Declare the pin used for the DCI ignition system
	DDRD |= (1 << PIND4);						// Ignition pin
	PORTD &= ~(1 << PIND4);						// Turn ignition pin off
	sei(); 	// Turn interrupts back on
}
void tablelookup(int *x, int *y)
{
	//for(unsigned char RPMIndex = 0; RPMIndex < )
}

// Interrupts with when low signal on crankshaft (60°BTDC)
ISR(INT0_vect)
{
	engine.rpm_c = TCNT1; 	// Store the latest cycle value
	TCNT1 = 0; 				// Initialize the cycle counter
	if (ovf == 1) {			// If the cycle was longer than 0,262 sec
		ovf = 0;			// To be implemented later !!!!!!!!!!!!!!!!!!!!
		return;
	}
	int x_ign_tab, y_ign_tab;
	tablelookup(x_ign_tab, y_ign_tab);
}
ISR(TIMER1_OVF_vect)
{

	ovf = 1; 								// over flow occurred
}
ISR(TIMER1_COMPB_vect)
{
	PORTD ^= (1 << PIND4);
	TIMSK1 &= ~(1 << OCIE1B);
	//PORTD |= (1 << PIND4);						// Turn on ignition
	//PORTD &= ~(1 << PIND4);						// Turn off ignition
}

//Crank high
ISR(INT1_vect)
{
	//PORTD |= (1 << PIND4);						// Turn on ignition
	//PORTD &= ~(1 << PIND4);						// Turn off ignition
	//PORTD ^= (1 << PIND4);
	EIMSK &= ~(1 << INT1);						// Disable INT1 interrupt
}

void ign_tab_init()
{
	/*double A[DiffNr][ANr] =
	{					// SFOC polynomial constants (Array) line 1 is group 1 ...
		{-2.0, 8.0, 8.0, 8.0, 8.0},
		{208.4, -0.06854, -0.006891, 0.00006125, 0}
	};
	// Fixment to call a function with a two dimensional array

	double **Afix = new double*[DiffNr];

	for (int i = 0; i < DiffNr; i++)
    {
    	Afix[i] = A[i];
	}


}*/

}

