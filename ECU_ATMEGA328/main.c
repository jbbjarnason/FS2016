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



int main(void)
{
	uartInit(57600); // baud rate 57k
	initIgnition();
	print_string("START");
	new_line();

	for (;;)
	{
		startADC();
		print_string("A0"); print_int(sensor_reading[0]);
		print_string("A1"); print_int(sensor_reading[1]);
		//println(engine.ign);
		//printchar('C');
		//println(engine.rpm_c);
		//delayms(1000);
	}
}
