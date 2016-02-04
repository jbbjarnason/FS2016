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

int main(void)
{

	uartInit(57600); // baud rate 57k
	ignInit();
	println(1234);
	println(1);


	for (;;)
	{




	}
}
