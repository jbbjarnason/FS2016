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
	//Set baud rate to 2 Mbps
	UCSR0A |= (1<<U2X0);
	UBRR0H = 0;
	UBRR0L = 0;
	//UBRR0H = (unsigned char)(baud_rate>>8); //Last 4 bits
	//UBRR0L = (unsigned char)baud_rate;		//First 8 bits.
	// Enable receiver and transmitter
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	//Set frame format at 8 data bits and 2 stop bits.
	UCSR0C |= 0x0E;
	while(!((UCSR0A & 0x20) == 0x20)){ }
	UDR0 = 10; // new line
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
	while(!((UCSR0A & 0x20) == 0x20)){ }
	UDR0 = 32; // whitespace
}
//Send Byte over to terminal
void print_byte(uint16_t data)
{
	unsigned int div = 100;		// Divider to divide data with
	char start = 0;
	char cnt = 3;
	for (int i = 1; i <= cnt; i++)
	{
		char send = data / div + 48; // calculate the Ascii for each number
		if(send != 48 || start == 1 || i == cnt)
		{
			//Wait until hardware is ready to send data, UDRE0 = Data register empty
			print_char(send);
			start = 1;
		}
		data %= div;
		div /= 10;
	}
}
//Send Integers over to terminal
void print_int(unsigned int data)
{
	unsigned int div = 10000;		// Divider to divide data with
	char start = 0;
	char cnt = 5;
	for (int i = 1; i <= cnt; i++)
	{
		char send = data / div + 48; // calculate the Ascii for each number
		if(send != 48 || start == 1 || i == cnt)
		{
			//Wait until hardware is ready to send data, UDRE0 = Data register empty
			print_char(send);
			start = 1;
		}
		data %= div;
		div /= 10;
	}
	new_line();
}
//Send Integers over to terminal
void print_long(unsigned long data)
{
	unsigned long div = 1000000000;		// Divider to divide data with
	char start = 0;
	char cnt = 10;
	for (int i = 1; i <= cnt; i++)
	{
		char send = data / div + 48; // calculate the Ascii for each number
		if(send != 48 || start == 1 || i == cnt)
		{
			//Wait until hardware is ready to send data, UDRE0 = Data register empty
			print_char(send);
			start = 1;
		}
		data %= div;
		div /= 10;
	}
	new_line();
}
void print_hex(unsigned long data)
{
	print_char('0');
	print_char('x');
	char start = 0;
	for (int i = 0; i < 8; i++)
	{
		// Shifting every nibble to the least significant nibble to transmit
		unsigned int send = (data >> (4*(8 - (i + 1)))) & 0xF;
		if (send != 0 && start == 0)
			start = 1;				// Start uarting when first nibble is more than zero
		if (send < 9 && start == 1)
			print_char(send + 48); 	// send ASCII of numbers 0 - 9
		else if (start == 1)
			print_char(send + 55); 	// send ASCII of letter A - F
	}
	new_line();
}

void print_char(unsigned char data)
{
	while(!((UCSR0A & (1 << UDRE0))));
	UDR0 = data;
}
void new_line()
{
	while(!((UCSR0A & (1 << UDRE0))));
	UDR0 = 10; // new line
}
// Attention the character array needs to end with NULL (0)
void print_string(char * data)
{
	int i = 0;
	// loop which print strings till null is reached or more than 20 characters (for safety)
	while(data[i] != 0 || i > 20)
		print_char(data[i++]);
	//new_line();
	while(!((UCSR0A & (1 << UDRE0)) == (1 << UDRE0))){ }
	UDR0 = 32; // space
}
