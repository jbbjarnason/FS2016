/*
 * helpers.h
 *
 *  Created on: 25. apr. 2016
 *      Author: JonB
 */

#ifndef LIBRARY_HELPERS_H_
#define LIBRARY_HELPERS_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART.h"
#include "global.h"
#include "adc.h"

uint8_t interpolation(uint16_t value, uint16_t x1, uint16_t x2);
//uint8_t average(uint8_t vector[], uint8_t length);
uint8_t median(uint8_t array[], uint8_t length);
uint16_t lookup_table(uint16_t table[], uint8_t max_length, uint16_t compare);



void print_serial();
void print_load_indexes();
void print_injection_indexes();
void print_ignition_indexes();
void print_interpolation();
void print_Analog_1();
void print_Analog_2();
void print_RPM();

#endif /* LIBRARY_HELPERS_H_ */
