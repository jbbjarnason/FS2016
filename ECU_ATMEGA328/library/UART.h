/*
 * UART.h
 *
 *  Created on: 31. jan. 2016
 *      Author: JonB
 */

#ifndef LIBRARY_UART_H_
#define LIBRARY_UART_H_

#include <avr/io.h>
#include "global.h"

#define CLOCKSPEED 16000000

void uartInit(uint32_t baud_rate);
void print(unsigned int data);
void print_byte(uint16_t data);
void print_int(unsigned int data);
void print_long(unsigned long data);
void print_hex(unsigned long data);
void print_char(unsigned char data);
void print_string(char * data);
void new_line();

uint16_t receive_to_int();

volatile uint8_t buffer_index;
volatile unsigned char buffer[10];



#endif /* LIBRARY_UART_H_ */
