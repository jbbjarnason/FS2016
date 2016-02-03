/*
 * UART.c
 *
 *  Created on: 31. jan. 2016
 *      Author: JonB
 */

#include "UART.h"


void uartInit(uint32_t baud_rate)
{
	baud_rate = CLOCKSPEED / 16 / baud_rate - 1;
	//Set baud rate
	UBRR0H = (unsigned char)(baud_rate>>8); //Last 4 bits
	UBRR0L = (unsigned char)baud_rate;		//First 8 bits.
	// Enable receiver and transmitter
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	//Set frame format at 8 data bits and 2 stop bits.
	UCSR0C |= 0x0E;
}

//Send Integers over to terminal
void print(unsigned int data)
{
	unsigned int div = 10000;		// Divider to divide data with
	char start = 0;
	char cnt = 5;
	for (int i = 1; i <= cnt; i++)
	{
		char send = data / div + 48; // calculate the Ascii for each number
		if(send != 48 || start == 1 || i == cnt)
		{
			//Wait until hardware is ready to send data.
			while(!((UCSR0A & 0x20) == 0x20)){ }
			UDR0 = send;
			start = 1;
		}
		data %= div;
		div /= 10;
	}
}

void println(unsigned int data)
{
	print(data);
	while(!((UCSR0A & 0x20) == 0x20)){ }
	UDR0 = 10; // new line
}
