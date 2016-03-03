/*
 * ign.h
 *
 *  Created on: 3. feb. 2016
 *      Author: JonB
 */

#ifndef LIBRARY_IGN_H_
#define LIBRARY_IGN_H_

#define CRANK_SIGNAL_ANGLE	60		// Angle from Low crank signal to top dead center
#define IGN_TIME 			100		// 100 * 4 µs = 400 µs for ignition pulse

#include <avr/io.h>
#include <avr/interrupt.h>
#include "global.h"
#include "UART.h"

void ignInit();
void ign_tab_init();
char ovf; // overflow of cycle timer

volatile struct engine_t engine;
volatile struct ignition_t table;



#endif /* LIBRARY_IGN_H_ */
