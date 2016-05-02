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
#include "global.h"
#define ADC_CHANNELS 5

void initSensors();
void startADC();
uint8_t readADC(uint8_t pin);

/*
 * ADC channel 0 Wideband sensor
 * ADC channel 1 Intake air temperature
 * ADC channel 2 Throttle position sensor
 * ADC channel 3 Coolant temperature
 * ADC channel 4 Manifold absolute pressure after restrictor
 * ADC channel 5 Oil temp
 * ADC channel 7 Manifold absolute pressure intake manifold
 */
uint8_t sensor_reading[ADC_CHANNELS];
uint8_t prev_sensor_reading;
uint8_t sensor_index;



#endif /* LIB_ADC_H_ */
