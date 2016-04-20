/*
 * delay.h
 *
 *  Created on: 3. feb. 2016
 *      Author: JonB
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <UART.h>

#ifndef LIBRARY_DELAY_H_
#define LIBRARY_DELAY_H_

unsigned long millis;

void delayInit();
void set_millis(unsigned long set);
unsigned long read_millis();
void delayms(unsigned int delay);
void delayus(unsigned int delay);

#endif /* LIBRARY_DELAY_H_ */
