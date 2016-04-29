/*
 * main.c
 *
 *  Created on: 3. feb. 2016
 *      Author: JonB
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <UART.h>
#include <ign.h>
#include <delay.h>
#include <adc.h>
#include <inj.h>
#include <helpers.h>
#include <global.h>



uint8_t average(uint8_t vector[], uint8_t length)
{
	uint16_t sum = 0;
	for (uint8_t i = 0; i < length; i++)
		sum += vector[i];
	//print_char('s'); print_int(sum);
	return sum / length;
}



int main(void)
{
	uartInit(57600);// Baud rate 57k
	initIgnition();	// Initialize ignition
	initSensors();	// Initialize analog sensors
	initInjection();// Initialize injection
	print_string("START");
	new_line();
	//print_int(interpolation(9400, 9375, 10000));
	//print_string("REV_LIMIT_COUNTS"); print_int(REV_LIMIT_COUNTS);
	//print_string("FUEL_CUT_RPM_COUNTS"); print_int(FUEL_CUT_RPM_COUNTS);
	// debugging pins
	DDRB |= (1 << PINB3) | (1 << PINB4);
	PORTB &= ~(1 << PINB3);
	PORTB &= ~(1 << PINB4);
	initGlobalVariables();

	uint8_t temp_cnt = 0;
	uint8_t temp_ave = 0;
	for (;;)
	{

		//print_char('a'); print_int(MAP_PIN);
		//print_int(readADC(MAP_PIN));
		// Routine to get median from the MAP sensor to find relevant minimum value
		engine_minMapAve[temp_cnt++] = readADC(MAP_PIN);
		temp_cnt = temp_cnt % MAP_AVERAGE_COUNTS;
		temp_ave = median(engine_minMapAve, MAP_AVERAGE_COUNTS);
		if (temp_ave < engine_minMAP)
			engine_minMAP = temp_ave;

		//print_int(temp_ave);
		//print_char(new_rpm);
		// if new rpm value arrives is calculated new index for RPM in the mapping tables
		if (new_rpm)
		{

			lowRPMindexIgn = 0;
			highRPMindexIgn = MAX_RPM_TABLE_LENGTH - 1;

			for (uint8_t RPMIndex = 0; RPMIndex < MAX_RPM_TABLE_LENGTH; RPMIndex++)
			{
				if (RPM_IGN_C[RPMIndex] > engine_rpm_c) {
					lowRPMindexIgn = RPMIndex;
				} else if (RPM_IGN_C[RPMIndex] < engine_rpm_c) {
					highRPMindexIgn = RPMIndex;
					break;
				} else if (RPM_IGN_C[RPMIndex] == engine_rpm_c) {
					lowRPMindexIgn = RPMIndex;
					highRPMindexIgn = RPMIndex;
					break;
				}
			}
			p_ign = 100 - interpolation(engine_rpm_c, RPM_IGN_C[highRPMindexIgn], RPM_IGN_C[lowRPMindexIgn]);


			lowRPMindexInj = 0;
			highRPMindexInj = MAX_RPM_TABLE_LENGTH - 1;

			for (uint8_t RPMIndex = 0; RPMIndex < MAX_RPM_TABLE_LENGTH; RPMIndex++)
			{
				if (RPM_INJ_C[RPMIndex] > engine_rpm_c) {
					lowRPMindexInj = RPMIndex;
				} else if (RPM_INJ_C[RPMIndex] < engine_rpm_c) {
					highRPMindexInj = RPMIndex;
					break;
				} else if (RPM_INJ_C[RPMIndex] == engine_rpm_c) {
					lowRPMindexInj = RPMIndex;
					highRPMindexInj = RPMIndex;
					break;
				}
			}
			p_inj = 100 - interpolation(engine_rpm_c, RPM_INJ_C[highRPMindexInj], RPM_INJ_C[lowRPMindexInj]);
			//uint16_t indexes = lookup_table(RPM_IGN_C, MAX_RPM_TABLE_LENGTH, engine_rpm_c);
			//lowRPMindexIgn = indexes & 0xFF;
			//highRPMindexIgn = (indexes >> 8);
			//print_char('I'); print_int(indexes);
			//lookup_table(&lowRPMindex, &highRPMindex, RPM_IGN_C, MAX_RPM_TABLE_LENGTH, engine_rpm_c);
			// Check the weight of the current RPM compared to the array in scale 0-100%

			//print_string("low"); print_int(RPM_IGN_C[lowRPMindexIgn]);
			//print_string("high"); print_int(RPM_IGN_C[highRPMindexIgn]);
			//print_string("cur"); print_int(engine_rpm_c);
			//print_char('p'); print_int(p_ign);

			PORTB ^= (1 << PINB3);
			// if second rpm value arrives is calculated new index for load in the mapping tables
			if (second_rpm){
				// gera if temp_kpa � sta� engine-minmap, nota signed int !!!!!
				uint16_t temp_kpa;
				if (engine_minMAP < 4)
					temp_kpa = 0;
				else
					temp_kpa = (long) 1289 * engine_minMAP / 1000 - 5;
				//indexes = lookup_table(LOAD, MAX_LOAD_TABLE_LENGTH, temp_kpa);
				//lowMAPindex = indexes & 0xFF;
				//highMAPindex = (indexes >> 8);
				//print_string("MAP"); print_int(temp_kpa);
				engine_MAP = temp_kpa;



				lowMAPindex = 0;
				highMAPindex = MAX_LOAD_TABLE_LENGTH - 1;

				for (uint8_t LOADIndex = 0; LOADIndex < MAX_LOAD_TABLE_LENGTH; LOADIndex++)
				{
					if (LOAD[LOADIndex] < temp_kpa) {
						lowMAPindex = LOADIndex;
					} else if (LOAD[LOADIndex] > temp_kpa) {
						highMAPindex = LOADIndex;
						break;
					} else if (LOAD[LOADIndex] == temp_kpa) {
						lowMAPindex = LOADIndex;
						highMAPindex = LOADIndex;
						break;
					}
				}

				q = interpolation(temp_kpa, LOAD[lowMAPindex], LOAD[highMAPindex]);

				//print_char('q');print_int(q);
				//print_char('L');print_int(LOAD[lowMAPindex]);
				//print_char('H');print_int(LOAD[highMAPindex]);

				//print_string("kpa"); print_int(temp_kpa);
				PORTB ^= (1 << PINB4);
				//print_int(engine_minMAP);

				engine_minMAP = 255;
			}
			second_rpm = !second_rpm;
			new_rpm = false;
		}
	}
}
