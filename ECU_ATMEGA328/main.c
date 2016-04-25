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



int main(void)
{
	uartInit(57600);// Baud rate 57k
	initIgnition();	// Initialize ignition
	initSensors();	// Initialize analog sensors
	initInjection();// Initialize injection
	print_string("START");
	new_line();
	print_string("REV_LIMIT_COUNTS"); print_int(REV_LIMIT_COUNTS);
	print_string("FUEL_CUT_RPM_COUNTS"); print_int(FUEL_CUT_RPM_COUNTS);
	for (;;)
	{


		//startADC();
		//print_string("A0"); print_int(sensor_reading[0]);
		//print_string("A1"); print_int(sensor_reading[1]);
		//println(engine.ign);
		//printchar('C');
		//println(engine.rpm_c);
		//delayms(100);
	}
}
