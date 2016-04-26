/*
 * main.c
 *
 *  Created on: 3. feb. 2016
 *      Author: JonB
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <UART.h>
#include <ign.h>
#include <delay.h>
#include <adc.h>
#include <inj.h>
#include <helpers.h>
#include <global.h>



uint8_t average(uint8_t vector[], uint8_t length)
{
	uint16_t sum = 0;
	for (uint8_t i = 0; i < length; i++)
		sum += vector[i];
	print_char('s'); print_int(sum);
	return sum / length;
}


int main(void)
{
	uartInit(57600);// Baud rate 57k
	initIgnition();	// Initialize ignition
	initSensors();	// Initialize analog sensors
	initInjection();// Initialize injection
	print_string("START");
	new_line();
	//print_int(interpolation(9400, 9375, 10000));
	//print_string("REV_LIMIT_COUNTS"); print_int(REV_LIMIT_COUNTS);
	//print_string("FUEL_CUT_RPM_COUNTS"); print_int(FUEL_CUT_RPM_COUNTS);
	// debugging pins
	DDRB |= (1 << PINB3) | (1 << PINB4);
	PORTB &= ~(1 << PINB3);
	PORTB &= ~(1 << PINB4);
	initGlobalVariables();

	uint8_t temp_cnt = 0;
	uint8_t temp_ave = 0;
	for (;;)
	{

		//print_char('a'); print_int(MAP_PIN);
		//print_int(readADC(MAP_PIN));
		// Routine to average specific times to find the minimum value from the MAP sensor
		engine_minMapAve[temp_cnt++] = readADC(MAP_PIN);
		//print_char('c'); print_int(engine_minMapAve[temp_cnt - 1]);
		temp_cnt = temp_cnt % MAP_AVERAGE_COUNTS;
		temp_ave = median(engine_minMapAve, MAP_AVERAGE_COUNTS);

		print_int(temp_ave);
		//print_char(new_rpm);
		// if new rpm value arrives is calculated new index for RPM in the mapping tables
		if (new_rpm)
		{
			new_rpm = false;
			PORTD ^= (1 << PIND7);
			// if second rpm value arrives is calculated new index for load in the mapping tables
			if (second_rpm){

			}
			second_rpm ^= second_rpm;
		}
	}
}
