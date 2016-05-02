/*
 * global.c
 *
 *  Created on: 25. apr. 2016
 *      Author: JonB
 */
#include "global.h"

void initGlobalVariables()
{
	engine_MAP = 0;
	second_rpm = false;
	engine_minMAP = 255;
	engine_MAP = sensor_reading[MAP_PIN];
	engine_MAP2 = sensor_reading[MAP2_PIN];
	engine_iat = 20;
	engine_tps = sensor_reading[TPS_PIN];

	accel_enrich = 0;
	print_ser = 0;
}

