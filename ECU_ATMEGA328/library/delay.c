/*
 * delay.c
 *
 *  Created on: 3. feb. 2016
 *      Author: JonB
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "delay.h"


void delayInit()
{
	// disable interrupts
	cli();
	// Initialize Timer 2 to interrupt every 1 ms
	// I will force the values to initialize the timer right, hard code it.
	TCCR2A = (1 << WGM21);	// Clear timer on compare match
	TCCR2B = (1 << CS22); 	// Prescale timer with 64, 16 MHz / 64 = 250 KHz => 4µs
	TCNT2 = 0;				// Initialize counter to zero
	OCR2A = 124; 			// Interrupt 250 counts 0 - 249, 250 * 4µs = 1 ms
	TIMSK2 = (1 << OCIE2A);	// Enable compare match A
	sei();					// Enable interrupts again

	// Test pin
	DDRB |= (1 << PINB0);
}
void set_millis(unsigned long set)
{
	millis = set;
}
unsigned long read_millis()
{
	return millis;
}

void delayms(unsigned int delay)
{
	for(unsigned int i = 0; i < delay; i++)
	{
		for(unsigned int j = 0; j < 1978; j++){
			__asm__("nop\n\t");
		}
	}
}
void delayus(unsigned int delay) {
	for(unsigned int i = 0; i < delay; i++)
		for(unsigned int j = 0; j < 6; j++)
			__asm__("nop\n\t");
}


ISR(TIMER2_COMPA_vect)
{
	PORTB ^= (1 << PINB0);
	millis++;
}
