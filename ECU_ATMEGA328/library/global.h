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
#define STARTING_RPM			500
#define STARTING_COUNTS			60000 / STARTING_RPM * 1000 / 4
#define IGN_COUNTS				250		// Spark for 250 counts * 4 탎 = 1ms
#define RPM_LIMIT				9100
#define REV_LIMIT_COUNTS		60000 / RPM_LIMIT * 1000 / 4
#define MAX_DWELL_TIME			9000 / TIMER1_US_CONST


struct engine_t
{
	unsigned int rpm_c; 	// RPM cycle in 4탎 (counter values)
	char status;			// Is the engine on (1 On, 0 off)
	char ign;				// Is time to spark (1 On, 0 off)
};

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
