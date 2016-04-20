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



int main(void)
{
	uartInit(57600); // baud rate 57k
	ignInit();
	print_string("START");
	new_line();

	for (;;)
	{
		//println(engine.ign);
		//printchar('C');
		//println(engine.rpm_c);
		//delayms(1000);
	}
}
