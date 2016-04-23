/*
 * ADC.h
 *
 *  Created on: 1. mar. 2016
 *      Author: JonB
 */

#ifndef LIB_ADC_H_
#define LIB_ADC_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#define ADC_CHANNELS 6

void initSensors();
void startADC();
uint8_t readADC(uint8_t pin);

uint8_t sensor_reading[ADC_CHANNELS];
uint8_t prev_sensor_reading;
uint8_t sensor_index;



#endif /* LIB_ADC_H_ */
