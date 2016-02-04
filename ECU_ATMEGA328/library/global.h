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

#define TIMER1_US_CONST		4		// Timer 1 prescaled to 4 µs


struct engine_t
{
	uint32_t rpm_c; 	//rpm cycle in µs
};


struct ignition_t
{
	unsigned char RPMLength;                        ///< The length of the RPM axis array
	unsigned char LoadLength;                       ///< The length of the Load axis array
	unsigned int RPM[MAINTABLE_MAX_RPM_LENGTH];    ///< The array of RPM (X) axis values
	unsigned long Cycle[MAINTABLE_MAX_RPM_LENGTH];	// Cycle in µs
	unsigned char Load[MAINTABLE_MAX_LOAD_LENGTH];  ///< The array of Load (Y) axis values
	float Table[MAINTABLE_MAX_MAIN_LENGTH]; ///< The table as an array of values
};


#endif /* LIBRARY_GLOBAL_H_ */
