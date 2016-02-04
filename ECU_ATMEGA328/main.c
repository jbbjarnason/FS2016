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

volatile struct engine_t engine;

int main(void)
{
	uartInit(57600); // baud rate 57k
	ignInit();
	println(1234);
	println(1);

	for (;;)
	{
		printchar('C');
		println(engine.rpm_c);
		delayms(1000);
	}
}
