/*
 * global.h
 *
 *  Created on: 3. feb. 2016
 *      Author: JonB
 */

#ifndef LIBRARY_GLOBAL_H_
#define LIBRARY_GLOBAL_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "adc.h"

void initGlobalVariables();

// DEFINE PIN NUMBERS
#define WB_PIN 0	//wideband
#define IAT_PIN 1	//intake air temp
#define TPS_PIN 2	//throttle position
#define CLT_PIN 3	//coolant temp
#define MAP2_PIN 4	//manifold absoulute pressure after restrictor
#define OT_PIN 5	//oil temp
#define MAP_PIN 7	//manifold absolute pressure intake

#define MAINTABLE_MAX_RPM_LENGTH		23
#define MAINTABLE_MAX_LOAD_LENGTH		1
#define MAINTABLE_MAX_MAIN_LENGTH		300

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

#define TIMER1_US_CONST			4		// Timer 1 prescaled to 4 탎
#define TIMER0_US_CONST			64		// Timer 0 prescaled to 64 탎
//#define STARTING_RPM			500
//#define STARTING_COUNTS			60000 / STARTING_RPM * 1000 / 4
//#define IGN_COUNTS				250		// Spark for 250 counts * 4 탎 = 1ms
#define RPM_LIMIT				9100
#define REV_LIMIT_COUNTS		60000000 / RPM_LIMIT / TIMER1_US_CONST
#define FUEL_CUT_RPM			9000
#define FUEL_CUT_RPM_COUNTS		60000000 / FUEL_CUT_RPM / TIMER1_US_CONST
#define MAX_DWELL_TIME			9000 / TIMER1_US_CONST
#define MAP_AVERAGE_COUNTS		5		// Has to be less than 256

#define BOOST_CUTOFF			62		// Serial value for 76 kpa Boost controller cuts the boost at 76kpa (before turbine) (serial = 0.7753*kpa + 4.221)

#define MAX_RPM_TABLE_LENGTH			8
#define MAX_LOAD_TABLE_LENGTH			8

#define INJECTOR_OPENING_TIME			1400 		// injector opening time in 탎, 1000탎 = 1ms
#define INTAKE_VALVE_DEGREES			45			// Intake valve fully open in degrees

#define ENGINE_CC						500			// 500 cc polaris motor

#define PULSE_DIVIDE					2			// number of injector pulses one round of the camshaft
#define NR_OF_INJ_PER_CYL				2			// number of injector per cylender
#define INJ_SIZE						5860		// Injector size 5860 mg/s
#define R								287			// Gas constant J/(kg K)

#define FUEL_CONST						74324		// FUEL_CONST = ENGINE_CC * 10^9 / (R*PULSE_DIVIDE*NR_OF_INJ_PER_CYL*INJ_SIZE)


#define TPS_TIME_THRESHOLD				200			// TPS time threshold in milliseconds
#define TPS_THRESHOLD					30			// TPS threshold of change after time, in 0-255 (keep in mind zero is around 50 and max 200 WOT)
#define TPS_ACCEL_ENRICH				1			// Enrichment factor of change, TPS_ACCEL_ENRICH * Change in 탎



uint8_t lowMAPindex;
uint8_t highMAPindex;
uint8_t lowRPMindexIgn;
uint8_t highRPMindexIgn;
uint8_t lowRPMindexInj;
uint8_t highRPMindexInj;
uint8_t p_ign;									// interpolation of RPM
uint8_t p_inj;
uint8_t q;									// interpolation of MAP
uint16_t IGN[MAX_RPM_TABLE_LENGTH][MAX_LOAD_TABLE_LENGTH]; 	// ignition table
uint8_t VE[MAX_RPM_TABLE_LENGTH][MAX_LOAD_TABLE_LENGTH]; 	// volumetric efficiency table
uint8_t AFR[MAX_RPM_TABLE_LENGTH][MAX_LOAD_TABLE_LENGTH]; 	// air to fuel ratio table
uint16_t RPM_INJ_C[MAX_RPM_TABLE_LENGTH];					// RPM vector for Injection in 4탎 counts
uint16_t RPM_IGN_C[MAX_RPM_TABLE_LENGTH];					// RPM vector for Ignition in 4탎 counts
uint8_t LOAD[MAX_LOAD_TABLE_LENGTH];						// Load vector of MAP values in kPa
uint8_t DWELL[MAX_RPM_TABLE_LENGTH];						// Dwell duty cycle vector

volatile uint16_t engine_rpm_c;							// RPM cycle in 4탎 (counter values)
volatile uint8_t engine_status;							// Is the engine on (1 On, 0 off)
volatile uint8_t engine_ign;							// Is time to spark (1 On, 0 off) /*********UNNESSASARY **********/
volatile uint8_t engine_inj;							// Is time to turn on the injection
volatile uint16_t engine_MAP;							// Minimum average of values from the MAP sensor in kpa
volatile uint8_t engine_minMapAve[MAP_AVERAGE_COUNTS]; 	// Measured values from the MAP sensor
volatile uint8_t engine_minMAP;							// Minimum of average values, when intake valve is fully open
volatile uint8_t engine_kpa;							// MAP sensor value in kPa
volatile uint16_t engine_MAP2;							// Minimum average of values from the MAP2 sensor in kpa
volatile uint8_t boost_ctrl;							// Boolean value for creating pwm for boost controller (1 On, 0 off)
volatile uint8_t duty_on;
volatile uint8_t duty_off;
volatile long on_time;
volatile long off_time;
volatile uint8_t engine_iat;							// Intake air temperature
volatile uint8_t engine_tps;							// Throttle position
volatile uint8_t engine_afr;							// Air to fuel ratio

//volatile uint8_t VE_inter;
//volatile uint16_t AFR_inter;
//volatile uint32_t degree;

volatile uint8_t accel_enrich;							// Acceleration enrichment for throttle position in 탎






uint8_t new_rpm;							// Boolean to calculate new indexes for new rpm in mapping arrays
uint8_t second_rpm;							// Boolean to calculate new MAP index

uint8_t print_ser;
//uint8_t receive_ser;

/*struct engine_t
{
	unsigned int rpm_c; 			// RPM cycle in 4탎 (counter values)
	uint8_t status;					// Is the engine on (1 On, 0 off)
	uint8_t ign;					// Is time to spark (1 On, 0 off)
	uint8_t inj;					// Is time to turn on the injection
	uint16_t MAP;					// Average of minimum values from
};*/

/*struct ignition_t
{
	unsigned char RPMLength;                        ///< The length of the RPM axis array
	unsigned char LoadLength;                       ///< The length of the Load axis array
	unsigned int RPM[MAINTABLE_MAX_RPM_LENGTH];    ///< The array of RPM (X) axis values
	unsigned long Cycle[MAINTABLE_MAX_RPM_LENGTH];	// Cycle in 탎
	unsigned char Load[MAINTABLE_MAX_LOAD_LENGTH];  ///< The array of Load (Y) axis values
	float Table[MAINTABLE_MAX_MAIN_LENGTH]; ///< The table as an array of values
	unsigned int dwell[MAINTABLE_MAX_RPM_LENGTH];			// dwell time in counts (4탎)
};*/


#endif /* LIBRARY_GLOBAL_H_ */
