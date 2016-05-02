/*
 * ADC.c
 *
 *  Created on: 1. mar. 2016
 *      Author: JonB
 */
#include "ADC.h"

// Take first measurement, for the average to work first cycle
void initSensors()
{
	for (int i = 0; i < ADC_CHANNELS; i++)
		sensor_reading[i] = readADC(i);
}
void startADC()
{
	// ADC Multiplexer Selection Register
	// Using Internal AVcc with external capacitor at aref pin,
	// highest 8 bits are in one register ADCH, analog pin 0 enabled
	ADMUX = (1 << REFS0) | (1 << ADLAR);
	// ADC Control and Status Register A
	// ADC enable, Prescale clock by division of 128, adc interrupt enable, ADC start conversion
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADIE) | (1 << ADSC);
	// Enable all analog pins
	DIDR0 = 0;
	// Initialize vector index counter
	sensor_index = 0;
	// Turn on interrupts
	sei();
}
/*
void transferFunctions()
{


	engine_MAP = 0;
	second_rpm = false;
	engine_minMAP = 255;
	engine_MAP = sensor_reading[MAP_PIN];
	engine_MAP_2 = sensor_reading[MAP2_PIN];
	engine_iat = 20;
	engine_tps = sensor_reading[TPS_PIN];


}
*/
uint8_t readADC(uint8_t pin)
{
	// Make the highest 8 bits in register ADCH (ADLAR)
	ADMUX = (1 << REFS0) | (1 << ADLAR) | (pin & 0x07);
	// initialize adc and start measurement
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADSC);
	// Wait for the ADC conversion to complete
	while (!(ADCSRA & (1 << ADIF)));
	// Clear the end of conversion flag
	ADCSRA |= (1 << ADIF);
	uint8_t read = ADCH;
	return read;
}
// ADC conversion complete interrupt
ISR(ADC_vect)
{
	prev_sensor_reading = sensor_reading[sensor_index];
	// 2 point average filter
	uint16_t tmp = ADCH + prev_sensor_reading;
	sensor_reading[sensor_index++] = (tmp >> 1); // divide with 2 by shifting right
	// run through all of the adc channels (pins)
	if (sensor_index >= ADC_CHANNELS - 1) { // stop reading, -1 to skip the MAP sensor
		ADCSRA &= ~(1 << ADIE);
		sensor_index = 0;
	} else { // go to next sensor
		ADMUX = (1 << REFS0) | (1 << ADLAR) | (sensor_index & 0x07);
		ADCSRA |= (1 << ADSC);
	}
}

