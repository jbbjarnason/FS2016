/*
 * global.h
 *
 *  Created on: 3. feb. 2016
 *      Author: JonB
 */

#ifndef LIBRARY_GLOBAL_H_
#define LIBRARY_GLOBAL_H_

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif


struct engine_t
{
	uint16_t rpm_c; 	//rpm counter
	char **ign_tab; 	//23x2 ignition table array
};



#endif /* LIBRARY_GLOBAL_H_ */
