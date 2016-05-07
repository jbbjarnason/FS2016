/*
 * ign.c
 *
 *  Created on: 3. feb. 2016
 * 		 Author: JonB
 */

#include "ign.h"
#include "global.h"
#include "delay.h"

unsigned int print_counter = 0;

void initIgnition()
{
	// Initialize structs
	initIgnTable();
	engine_rpm_c = 0;
	engine_ign = true;

	cli();	// Turn global interrupts off
	// Crankshaft interrupt pins
	EICRA |= (1 << ISC11) | (1 << ISC10);		// Set INT1 to rising edge
	// Crankshaft Low signal, comes 60° before top dead center
	EIMSK |= (1 << INT1);						// Enable INT1 interrupt
	// Clock to time from crank signal to ignition pulse
	TCCR1B = (1 << CS10) | (1 << CS11);		// Prescale to 4µs
	// Overflow interrupt for cycle less than 65536*4µs = 0,262144 s
	TIMSK1 = (1 << OCIE1A) | (1 << OCIE1B) | (1 << TOIE1); // Turn on compare match B interrupt
	// Initialize the counter value
	TCNT1 = 0;									// Zero counter 1
	OCR1A = 65535;
	OCR1B = 65535;
	// Declare the pin used for the TCI ignition system
	DDRD |= (1 << PIND4);
	PORTD &= ~(1 << PIND4);						// Turn ignition pin off

	// initialize boolean of new rpm value
	//new_rpm = true;
	sei(); 	// Turn global interrupts back on

}
void initIgnTable()
{
	// Initialize load vector
	LOAD[0] = 25;LOAD[1] = 36;LOAD[2] = 46;LOAD[3] = 58;LOAD[4] = 68;LOAD[5] = 80;LOAD[6] = 90;LOAD[7] = 101;

	// NEW ignition table 25.4.16 , NEED TO divide degrees with 10, store 8.0° as 80°, int instead of float
	IGN[7][0] = 130; IGN[7][1] = 100; IGN[7][2] = 294; IGN[7][3] = 341; IGN[7][4] = 341; IGN[7][5] = 341; IGN[7][6] = 341; IGN[7][7] = 341;
	IGN[6][0] = 130; IGN[6][1] = 100; IGN[6][2] = 286; IGN[6][3] = 332; IGN[6][4] = 332; IGN[6][5] = 332; IGN[6][6] = 332; IGN[6][7] = 332;
	IGN[5][0] = 130; IGN[5][1] = 100; IGN[5][2] = 279; IGN[5][3] = 323; IGN[5][4] = 323; IGN[5][5] = 323; IGN[5][6] = 323; IGN[5][7] = 323;
	IGN[4][0] = 130; IGN[4][1] = 100; IGN[4][2] = 271; IGN[4][3] = 314; IGN[4][4] = 314; IGN[4][5] = 314; IGN[4][6] = 314; IGN[4][7] = 314;
	IGN[3][0] = 130; IGN[3][1] = 100; IGN[3][2] = 263; IGN[3][3] = 305; IGN[3][4] = 305; IGN[3][5] = 305; IGN[3][6] = 305; IGN[3][7] = 305;
	IGN[2][0] = 130; IGN[2][1] = 100; IGN[2][2] = 255; IGN[2][3] = 296; IGN[2][4] = 296; IGN[2][5] = 296; IGN[2][6] = 296; IGN[2][7] = 296;
	IGN[1][0] = 130; IGN[1][1] = 100; IGN[1][2] = 248; IGN[1][3] = 287; IGN[1][4] = 287; IGN[1][5] = 287; IGN[1][6] = 287; IGN[1][7] = 287;
	IGN[0][0] = 50;  IGN[0][1] = 100; IGN[0][2] = 240; IGN[0][3] = 278; IGN[0][4] = 278; IGN[0][5] = 278; IGN[0][6] = 278; IGN[0][7] = 278;

	DWELL[0] = 40; DWELL[1] = 40; DWELL[2] = 40; DWELL[3] = 40; DWELL[4] = 40; DWELL[5] = 40; DWELL[6] = 40; DWELL[7] = 40;

	// New ignition RPM vector
	// Initialize RPM vector
	uint8_t temp_rpm[MAX_RPM_TABLE_LENGTH] = {15, 16, 27, 37, 48, 59, 70, 91}; // temporary rpm vector, expressed in RPM / 100
	for (uint8_t i = 0; i < MAX_RPM_TABLE_LENGTH; i++){
		RPM_IGN_C[i] = 600000 / ((long)temp_rpm[i] * TIMER1_US_CONST);
		print_string("IGN_RPM"); print_int(temp_rpm[i]);
		print_string("LOAD"); print_int(LOAD[i]);
		print_string("DWELL"); print_int(DWELL[i]);
		for (uint8_t j = 0; j < MAX_LOAD_TABLE_LENGTH; j++){
			print_string("IGN"); print_int(IGN[i][j]);
		}
		print_string("IGN_Done"); new_line();
	}

	/* kPa
		 * 101
		 * 90
		 * 80
		 * 68
		 * 58
		 * 46
		 * 36
		 * 25
		 *///1500, 1600, 2700, 3700, 4800, 5900, 7000, 9100 RPM


	/*table.RPMLength = MAINTABLE_MAX_RPM_LENGTH;
	table.LoadLength = MAINTABLE_MAX_LOAD_LENGTH;

	unsigned int temp_rpm_ign[MAINTABLE_MAX_RPM_LENGTH] =
			{ 500,700,1100,1500,1900,2300,2700,3100,3500,3900,4300,4700,
			5100,5500,5900,6300,6700,7100,7500,7900,8300,8700,9100};

	float temp_table[MAINTABLE_MAX_RPM_LENGTH] =
			{0.0, 8.0,	8.0, 8.0, 8.0, 12.4, 18.3, 24.2, 30.0, 30.0, 30.0, 30.0,
			30.0, 30.0, 30.0, 30.0, 30.0, 30.0, 30.0, 30.0, 30.0, 26.0, 18.0}; // Byrjaði á -2 breytti 27.3.16 til að testa

	uint8_t temp_dwell[MAINTABLE_MAX_RPM_LENGTH] =
				{40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
				40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40}; // duty cycle in %, 40%

	for(int i = 0; i < table.RPMLength; i++)
	{
		table.RPM[i] = temp_rpm_ign[i];
		unsigned long temp = 60000000 / ((long)temp_rpm_ign[i] * TIMER1_US_CONST) ; // in 4µs count values
		table.Cycle[i] = temp;
		table.Table[i] = temp_table[i];
		table.dwell[i] = temp_dwell[i]; // cycle - 40% duty cycle in counts
		print_string("RPM");print_int(temp_rpm_ign[i]);
		print_string("CycleCounts");print_long(temp);
		print_string("DwellDutyCycle"); print_int(temp_dwell[i]);
	}*/
}

// Interrupts on low signal on crankshaft (60°BTDC)
ISR(INT1_vect)										//******************
{
	engine_rpm_c = TCNT1; 	// Store the latest cycle value
	TCNT1 = 0; 				// Initialize the cycle counter

	startINJ();



	uint32_t degree = (((long)IGN[lowMAPindex][lowRPMindexIgn] * (100 - p_ign) * (100 - q)) +
					((long)IGN[lowMAPindex][highRPMindexIgn] * p_ign * (100 - q)) +
					((long)IGN[highMAPindex][lowRPMindexIgn] * (100 - p_ign) * q) +
					((long)IGN[highMAPindex][highRPMindexIgn] * p_ign * q)) / 100000;
	/*print_char('D'); print_int(degree);
	print_char('1'); print_int(IGN[lowRPMindexIgn][lowMAPindex]/10);
	print_char('2'); print_int(IGN[highRPMindexIgn][lowMAPindex]/10);
	print_char('3'); print_int(IGN[lowRPMindexIgn][highMAPindex]/10);
	print_char('4'); print_int(IGN[highRPMindexIgn][highMAPindex]/10);*/
	engine_ign = (engine_rpm_c > REV_LIMIT_COUNTS);

	/*uint8_t lowRPMIndex1 = 0;
	uint8_t highRPMIndex1 = table.RPMLength - 1;
	//print_char('C');print_int(engine_rpm_c);
	for (uint8_t RPMIndex = 0; RPMIndex < table.RPMLength; RPMIndex++)
	{
		if (table.Cycle[RPMIndex] > engine_rpm_c) {
			lowRPMIndex1 = RPMIndex;
		} else if (table.Cycle[RPMIndex] < engine_rpm_c) {
			highRPMIndex1 = RPMIndex;
			break;
		} else if (table.Cycle[RPMIndex] == engine_rpm_c) {
			lowRPMIndex1 = RPMIndex;
			highRPMIndex1 = RPMIndex;
			break;
		}
	}

	unsigned char degree1 = ((table.Table[highRPMIndex1] + table.Table[lowRPMIndex1]) / 2);*/
	//print_char('d'); print_int(degree1);
	// calculate counts for compare match B to SPARK !
	//uint32_t ign_coil_off = (unsigned long) engine_rpm_c * (CRANK_SIGNAL_ANGLE * 10 - degree) / 3600;
	uint16_t calc_counts = (engine_rpm_c / 360) * (CRANK_SIGNAL_ANGLE - degree);
	//print_char('o');print_int(ign_coil_off);
	//print_char('c');print_int(calc_counts);
	OCR1B = calc_counts; //- TCNT1;
	//print_char('e'); print_int(engine_rpm_c);
	//print_char('d'); print_int(degree);
	//uint16_t ign_coil_off = ((unsigned long) engine_rpm_c * (CRANK_SIGNAL_ANGLE * 10 - degree)) / 3600;
	//print_char('o');print_int(ign_coil_off);
	//print_char('c');print_int(calc_counts);
	// calculate count for compare match A to turn on the ignition coil
	//uint32_t calc_dwell = ((long)engine_rpm_c * ((table.dwell[highRPMIndex1] + table.dwell[lowRPMIndex1]) / 2)) / 100;
	uint32_t calc_dwell = ((long)engine_rpm_c * ((DWELL[lowRPMindexIgn] + DWELL[highRPMindexIgn]) / 2)) / 100;
	//print_char('H'); print_int(highRPMIndex1);
	//print_char('L'); print_int(lowRPMIndex1);
	if (OCR1B > MAX_DWELL_TIME) { // is the SPARK delay time more then maximum dwell time 9 ms ?
		OCR1A = OCR1B - MAX_DWELL_TIME;
	} else if (calc_dwell > MAX_DWELL_TIME) { // is the calculated dwell time to long ?
		OCR1A = engine_rpm_c - MAX_DWELL_TIME + OCR1B;
	} else { // use the calculated dwell time
		OCR1A = engine_rpm_c - calc_dwell + OCR1B;
	}
	//unsigned long dwell_delay = engine_rpm_c - ((4 * (long)engine_rpm_c) / 10);
	//OCR1A = (unsigned int) dwell_delay;

	/*print_counter++;
	 * if (print_counter > 100)
	{
		print_char('R'); print_int(engine_rpm_c);
		print_char('A'); print_int(OCR1A);
		print_char('B'); print_int(OCR1B);
		print_char('T'); print_int(TIMSK1);
		print_char('C'); print_int(TCNT1);
		print_string("low"); print_int(lowRPMIndex);
		print_string("high"); print_int(highRPMIndex);
		print_counter = 0;
	}*/
	new_rpm = true;			// Boolean used to indicate new_rpm which calculates new mapping values (main loop)
}

// Turn on coil
ISR(TIMER1_COMPA_vect)
{

	if (engine_ign)
		PORTD |= (1 << PIND4);
	else
		PORTD &= ~(1 << PIND4);
}
// Time to SPARK !!
ISR(TIMER1_COMPB_vect)
{
	PORTD &= ~(1 << PIND4); // Spark
}
// Safety for ignition coil overheating
ISR(TIMER1_OVF_vect)
{
	engine_ign = false;
}


