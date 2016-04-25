/*
 * inj.c
 *
 *  Created on: 23. apr. 2016
 *      Author: JonB
 */

#include "inj.h"


void initInjection()
{
	// Turn off global interrupts
	cli();
	// Initialize TIMER0
	// Prescale timer to 16 MHz / 128, 64 µs per count
	TCCR0B = (1 << CS00) | (1 << CS02);
	// Enable rising edge for interrupt 0
	EICRA |= (1 << ISC01) | (1 << ISC00);
	// Enable INT0 interrupt for cranksignal High
	EIMSK |= (1 << INT0);
	// External interrupt 0 turns on the overflow interrupt
	// overflow turns on compare match A after specified counts of overflow
	// compare match A turn either both on overflow and compare match B
	// Turn on global interrupts

	// Initialize engine injection boolean indicator
	engine_inj = true;
	// Declare the pin used for the TCI ignition system
	DDRD |= (1 << PIND5) | (1 << PIND6);
	PORTD &= ~(1 << PIND6);
	PORTD &= ~(1 << PIND5);
	sei();
}

// Calculate injector timing
ISR(INT0_vect) // Interrupts 2° after TDC
{
	TCNT0 = 0;
	// DEBUGG
	if (engine_inj)
		PORTD |= (1 << PIND5);
	else
		PORTD &= ~(1 << PIND5);


	// Check Rev limit
	if (engine_rpm_c < REV_LIMIT_COUNTS)
		engine_inj = false;
	// Fuel cut hysterisis
	if (!engine_inj){
		if (engine_rpm_c > FUEL_CUT_RPM_COUNTS)
			engine_inj = true;
		else
			return;
	}

	// Turn on overflow interrupt
	TIMSK1 |= (1 << TOIE1);



}
