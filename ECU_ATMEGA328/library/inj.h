/*
 * inj.h
 *
 *  Created on: 23. apr. 2016
 *      Author: JonB
 */

#ifndef LIBRARY_INJ_H_
#define LIBRARY_INJ_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART.h"
#include "global.h"
#include "ign.h"
#include "adc.h"

volatile uint8_t ovf_flag;
volatile uint8_t stop_flag;
volatile uint16_t timer0_ovf_a;
volatile uint16_t timer0_ovf_b;
volatile int16_t timer0_ovf;
volatile uint16_t timer1_counts;
volatile uint16_t counter;
volatile uint32_t inj_start_time;
volatile uint16_t inj_stop_time;
volatile uint32_t M_fuel1;
volatile uint8_t inj_flag;

void initInjection();
void initInjTable();




#endif /* LIBRARY_INJ_H_ */
