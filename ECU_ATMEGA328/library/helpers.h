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

uint8_t interpolation(uint16_t value, uint16_t x1, uint16_t x2);
//uint8_t average(uint8_t vector[], uint8_t length);
uint8_t median(uint8_t array[], uint8_t length);


#endif /* LIBRARY_HELPERS_H_ */
