/*
 * global.h
 *
 *  Created on: 3. feb. 2016
 *      Author: JonB
 */

#ifndef LIBRARY_GLOBAL_H_
#define LIBRARY_GLOBAL_H_

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
//#define STARTING_RPM			500
//#define STARTING_COUNTS			60000 / STARTING_RPM * 1000 / 4
//#define IGN_COUNTS				250		// Spark for 250 counts * 4 탎 = 1ms
#define RPM_LIMIT				9100
#define REV_LIMIT_COUNTS		60000000 / RPM_LIMIT / TIMER1_US_CONST
#define FUEL_CUT_RPM			9000
#define FUEL_CUT_RPM_COUNTS		60000000 / FUEL_CUT_RPM / TIMER1_US_CONST
#define MAX_DWELL_TIME			9000 / TIMER1_US_CONST
#define MAP_AVERAGE_COUNTS		5		// Has to be less than 256

#define MAX_RPM_TABLE_LENGTH			8
#define MAX_LOAD_TABLE_LENGTH			8



uint8_t lowMAPindex;						// The length of MAP axis
uint8_t highMAPindex;
uint8_t lowRPMindex;
uint8_t lowRPMindex;
uint8_t IGN_TABLE[MAX_RPM_TABLE_LENGTH][MAX_LOAD_TABLE_LENGTH];
uint16_t VE_TABLE[MAX_RPM_TABLE_LENGTH][MAX_LOAD_TABLE_LENGTH];
uint16_t AFR_TABLE[MAX_RPM_TABLE_LENGTH][MAX_LOAD_TABLE_LENGTH];

uint16_t engine_rpm_c;						// RPM cycle in 4탎 (counter values)
uint8_t engine_status;						// Is the engine on (1 On, 0 off)
uint8_t engine_ign;							// Is time to spark (1 On, 0 off) /*********UNNESSASARY **********/
uint8_t engine_inj;							// Is time to turn on the injection
uint16_t engine_MAP;						// Average of values from the MAP sensor

/*struct engine_t
{
	unsigned int rpm_c; 			// RPM cycle in 4탎 (counter values)
	uint8_t status;					// Is the engine on (1 On, 0 off)
	uint8_t ign;					// Is time to spark (1 On, 0 off)
	uint8_t inj;					// Is time to turn on the injection
	uint16_t MAP;					// Average of minimum values from
};*/

struct ignition_t
{
	unsigned char RPMLength;                        ///< The length of the RPM axis array
	unsigned char LoadLength;                       ///< The length of the Load axis array
	unsigned int RPM[MAINTABLE_MAX_RPM_LENGTH];    ///< The array of RPM (X) axis values
	unsigned long Cycle[MAINTABLE_MAX_RPM_LENGTH];	// Cycle in 탎
	unsigned char Load[MAINTABLE_MAX_LOAD_LENGTH];  ///< The array of Load (Y) axis values
	float Table[MAINTABLE_MAX_MAIN_LENGTH]; ///< The table as an array of values
	unsigned int dwell[MAINTABLE_MAX_RPM_LENGTH];			// dwell time in counts (4탎)
};


#endif /* LIBRARY_GLOBAL_H_ */
