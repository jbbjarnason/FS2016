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



/*uint8_t average(uint8_t vector[], uint8_t length)
{
	uint16_t sum = 0;
	for (uint8_t i = 0; i < length; i++)
		sum += vector[i];
	//print_char('s'); print_int(sum);
	return sum / length;
}*/



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
	DDRB |= (1 << PINB3) | (1 << PINB4) | (1 << PINB1);
	PORTB &= ~(1 << PINB1);
	PORTB &= ~(1 << PINB3);
	PORTB &= ~(1 << PINB4);
	initGlobalVariables();
	delayInit(); // keep track of milliseconds

	duty_off = 43;											// Duty cycle for boost controller
	duty_on = 7;											// Duty cycle for boost controller

	uint8_t temp_cnt = 0;
	uint8_t temp_ave = 0;

	uint8_t prev_TPS = 0;
	accel_enrich = 0;

	for (;;)
	{

		// Routine to get median from the MAP sensor to find relevant minimum value
		engine_minMapAve[temp_cnt++] = readADC(MAP_PIN);
		temp_cnt = temp_cnt % MAP_AVERAGE_COUNTS;
		temp_ave = median(engine_minMapAve, (int)MAP_AVERAGE_COUNTS);
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

			degree = (((long)IGN[lowMAPindex][lowRPMindexIgn] * (100 - p_ign) * (100 - q)) +
					((long)IGN[lowMAPindex][highRPMindexIgn] * p_ign * (100 - q)) +
					((long)IGN[highMAPindex][lowRPMindexIgn] * (100 - p_ign) * q) +
					((long)IGN[highMAPindex][highRPMindexIgn] * p_ign * q)) / 10000;


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

			VE_inter = (((long)VE[lowMAPindex][lowRPMindexInj] * (100 - p_inj) * (100 - q)) +
						((long)VE[lowMAPindex][highRPMindexInj] * p_inj * (100 - q)) +
						((long)VE[highMAPindex][lowRPMindexInj] * (100 - p_inj) * q) +
						((long)VE[highMAPindex][highRPMindexInj] * p_inj * q)) / 10000;
			AFR_inter = (((long)AFR[lowMAPindex][lowRPMindexInj] * (100 - p_inj) * (100 - q)) +
						((long)AFR[lowMAPindex][highRPMindexInj] * p_inj * (100 - q)) +
						((long)AFR[highMAPindex][lowRPMindexInj] * (100 - p_inj) * q) +
						((long)AFR[highMAPindex][highRPMindexInj] * p_inj * q)) / 1000;
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

			//PORTB ^= (1 << PINB3);
			// if second rpm value arrives is calculated new index for load in the mapping tables
			if (second_rpm){
				//print_char('s');print_int(inj_stop_time);
				// gera if temp_kpa í stað engine-minmap, nota signed int !!!!!
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
				//PORTB ^= (1 << PINB4);
				//print_int(engine_minMAP);
				//print_serial();
				engine_minMAP = 255;
			}
			second_rpm = !second_rpm;
			new_rpm = false;

		}

		//******************************************************************************************************//
		//******************************************* TPS Parameters *******************************************//
		//******************************************************************************************************//

		//TODO
		/*
		 * if(sensor_reading[TPA_PIN] > FULL_THROTTLE_THRESHOLD)		// When throttle is engaged more than 70%, the exhaust gas enrichment correction is disabled
		 * {
		 * 		Disable EGO enrichment
		 * }
		 */



		// Quick Throttle Acceleration
		if(TPS_count > TPS_CYCLE)
		{
			// Acceleration											// Quick throttle input gives small amount of extra fuel
			if(sensor_reading[TPS_PIN] > prev_TPS)					// Check if accelerating
			{

				uint8_t diff = sensor_reading[TPS_PIN] - prev_TPS;
				//print_char('d'); print_int(diff);

				if(diff > TPS_THRESHOLD)							// If throttle input is high the difference goes over the threshold
				{													// and activates the acceleration enrichment
					accel_enrich = diff * TPS_ACCEL_ENRICH;
					//print_char('D'); print_int(diff);
					//print_char('A'); print_int(accel_enrich);
				}
				else
					accel_enrich = 0;

			}
			prev_TPS = sensor_reading[TPS_PIN];
			TPS_count = 0;
		}
		TPS_count++;




		// Closed Throttle Deceleration Parameters
		//TODO  IDEA: increase the DEC_THRESH_COUNT when engine is cool so the injectors don't close when engine is in warmup enrichment mode
		if(sensor_reading[TPS_PIN] < IDLE_TPS_THRESH && engine_rpm_c < DEC_THRESH_COUNT)
		{												// If TPS sensor is in closed +5% position and the engine RPM is over idle RPM value
			dec_cut = false;										// the injectors are disabled
			print_char('C'); print_int(engine_inj);
		}
		else if(engine_rpm_c > REV_LIMIT_COUNTS)
		{
			dec_cut = true;
		}




		//*********************************************************************************************************//
		//************************************** Boost Controller Parameters **************************************//
		//*********************************************************************************************************//

		if(sensor_reading[MAP2_PIN] < BOOST_CUTOFF)					// Turn boost controller on when pressure is above threshold
		{
			if(duty_on > 40)										// Threshold parameters for max duty cycle at 20Hz
			{
				duty_on = 40;										// Max duty cycle = 85% at 20Hz, 40ms = 80% duty cycle
				duty_off = 10;										// 1/20Hz = 50ms -----> 50ms - duty_on = 10ms
			}
			else if(duty_on < 7)									// Threshold parameters for min duty cycle at 20Hz
			{
				duty_on = 7;										// Min duty cycle = 10% at 20Hz, 7ms = 14% duty cycle
				duty_off = 43;										// 1/20Hz = 50ms -----> 50ms - duty_on = 43ms
			}

			if(!boost_ctrl && (millis - off_time) > duty_off)		// Parameters for creating pwm at 20Hz
			{
				on_time = millis;
				PORTB |= (1 << PINB1);								// Turn on PINB1 (D9)
				boost_ctrl = true;
			}
			if(boost_ctrl && (millis - on_time) > duty_on)			// Parameters for creating pwm at 20Hz
			{
				off_time = millis;
				PORTB &= ~(1 << PINB1);								// Turn off PINB1 (D9)
				boost_ctrl = false;

				if(duty_on < 41 && duty_on > 6)						// Duty cycle increases with decreasing pressure in intake manifold
				{													// Duty cycle decreases with increasing pressure in intake manifold
					duty_on = (150/sensor_reading[MAP2_PIN])*7;
					duty_off = 50 - duty_on;
				}
			}
		}
		else														// Turn boost controller off when pressure is above threshold
		{
			PORTB &= ~(1 << PINB1);
			duty_on = 10;											// Put duty cycle to the original value
			duty_off = 40;
		}

	}
}
