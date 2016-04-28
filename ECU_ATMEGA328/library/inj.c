/*
 * inj.c
 *
 *  Created on: 23. apr. 2016
 *      Author: JonB
 */

#include "inj.h"

void initInjTable()
{
	// Initialize RPM vector
	uint8_t temp_rpm[MAX_RPM_TABLE_LENGTH] = {15, 20, 32, 44, 56, 67, 79, 91}; // temporary rpm vector, expressed in RPM / 100
	for (uint8_t i = 0; i < MAX_RPM_TABLE_LENGTH; i++){
		RPM_INJ_C[i] = 600000 / ((long)temp_rpm[i] * TIMER1_US_CONST);
		//print_string("INJ"); print_int(RPM_INJ_C[i]);
	}

	// Initialize load vector
	LOAD[0] = 25;LOAD[1] = 36;LOAD[2] = 46;LOAD[3] = 58;LOAD[4] = 68;LOAD[5] = 80;LOAD[6] = 90;LOAD[7] = 101;

	// Initializing Volumetric efficiency table
	VE[7][0] = 29; VE[7][1] = 29; VE[7][2] = 29; VE[7][3] = 100; VE[7][4] = 100; VE[7][5] = 96; VE[7][6] = 91; VE[7][7] = 87;
	VE[6][0] = 29; VE[6][1] = 29; VE[6][2] = 29; VE[6][3] = 96; VE[6][4] = 96; VE[6][5] = 92; VE[6][6] = 87; VE[6][7] = 83;
	VE[5][0] = 29; VE[5][1] = 29; VE[5][2] = 29; VE[5][3] = 92; VE[5][4] = 92; VE[5][5] = 87; VE[5][6] = 83; VE[5][7] = 79;
	VE[4][0] = 29; VE[4][1] = 29; VE[4][2] = 29; VE[4][3] = 85; VE[4][4] = 85; VE[4][5] = 81; VE[4][6] = 77; VE[4][7] = 73;
	VE[3][0] = 29; VE[3][1] = 29; VE[3][2] = 29; VE[3][3] = 80; VE[3][4] = 80; VE[3][5] = 76; VE[3][6] = 73; VE[3][7] = 69;
	VE[2][0] = 29; VE[2][1] = 29; VE[2][2] = 29; VE[2][3] = 76; VE[2][4] = 76; VE[2][5] = 72; VE[2][6] = 68; VE[2][7] = 65;
	VE[1][0] = 29; VE[1][1] = 29; VE[1][2] = 29; VE[1][3] = 69; VE[1][4] = 69; VE[1][5] = 66; VE[1][6] = 62; VE[1][7] = 59;
	VE[0][0] = 29; VE[0][1] = 29; VE[0][2] = 29; VE[0][3] = 65; VE[0][4] = 65; VE[0][5] = 61; VE[0][6] = 58; VE[0][7] = 55;
	// Initialize Air to fuel ratio table
	AFR[7][0] = 133; AFR[7][1] = 133; AFR[7][2] = 131; AFR[7][3] = 131; AFR[7][4] = 129; AFR[7][5] = 125; AFR[7][6] = 125; AFR[7][7] = 125;
	AFR[6][0] = 133; AFR[6][1] = 133; AFR[6][2] = 133; AFR[6][3] = 133; AFR[6][4] = 131; AFR[6][5] = 127; AFR[6][6] = 127; AFR[6][7] = 127;
	AFR[5][0] = 133; AFR[5][1] = 133; AFR[5][2] = 135; AFR[5][3] = 135; AFR[5][4] = 133; AFR[5][5] = 129; AFR[5][6] = 129; AFR[5][7] = 129;
	AFR[4][0] = 133; AFR[4][1] = 133; AFR[4][2] = 137; AFR[4][3] = 137; AFR[4][4] = 135; AFR[4][5] = 131; AFR[4][6] = 131; AFR[4][7] = 131;
	AFR[3][0] = 133; AFR[3][1] = 133; AFR[3][2] = 139; AFR[3][3] = 139; AFR[3][4] = 137; AFR[3][5] = 133; AFR[3][6] = 133; AFR[3][7] = 133;
	AFR[2][0] = 133; AFR[2][1] = 133; AFR[2][2] = 142; AFR[2][3] = 142; AFR[2][4] = 140; AFR[2][5] = 136; AFR[2][6] = 136; AFR[2][7] = 136;
	AFR[1][0] = 133; AFR[1][1] = 133; AFR[1][2] = 144; AFR[1][3] = 144; AFR[1][4] = 142; AFR[1][5] = 138; AFR[1][6] = 138; AFR[1][7] = 138;
	AFR[0][0] = 133; AFR[0][1] = 133; AFR[0][2] = 146; AFR[0][3] = 146; AFR[0][4] = 144; AFR[0][5] = 140; AFR[0][6] = 140; AFR[0][7] = 140;
	/* kPa
	 * 101
	 * 90
	 * 80
	 * 68
	 * 58
	 * 46
	 * 36
	 * 25
	 *///1500, 2000, 3200, 4400, 5600, 6700, 7900, 9100 RPM


}

void initInjection()
{
	// Turn off global interrupts
	cli();
	// Initialize Mapping tables
	initInjTable();
	// Initialize TIMER0
	// Prescale timer to 16 MHz / 128, 64 µs per count
	TCCR0B = (1 << CS00) | (1 << CS02);
	// Enable compare match a, b and overflow
	//TIMSK0 = (1 << OCIE0A) | (1 << OCIE0B) | (1 << TOIE0);
	// Enable rising edge for interrupt 0
	EICRA |= (1 << ISC01) | (1 << ISC00);
	// Enable INT0 interrupt for cranksignal High
	EIMSK |= (1 << INT0);
	// External interrupt 0 turns on the overflow interrupt
	// overflow turns on compare match A after specified counts of overflow
	// compare match A turn either both on overflow and compare match B
	// Turn on global interrupts

	// Initialize engine injection boolean indicator
	engine_inj = true;
	// Declare the pin used for the TCI ignition system
	DDRD |= (1 << PIND5) | (1 << PIND6);
	PORTD &= ~(1 << PIND6);
	PORTD &= ~(1 << PIND5);

	TCNT0 = 0;
	timer0_ovf = 0;
	sei();
}

// Calculate injector timing
ISR(INT0_vect) // Interrupts 2° after TDC
{
	TCNT0 = 0;
	counter = 0;
	inj_flag = true;

	// Check Rev limit
	if (engine_rpm_c < REV_LIMIT_COUNTS)
		engine_inj = false;
	// Fuel cut hysterisis
	if (!engine_inj){
		if (engine_rpm_c > FUEL_CUT_RPM_COUNTS)
			engine_inj = true;
		else
			return;
	}
	// Calculate injector ON time
	uint16_t intake_valve_open = (INTAKE_VALVE_DEGREES * (long)engine_rpm_c) / 360;
	inj_start_time = (((long)engine_rpm_c - TCNT1 + intake_valve_open) * TIMER1_US_CONST - INJECTOR_OPENING_TIME) / TIMER0_US_CONST;
	//print_char('V');print_int(intake_valve_open);
	//print_char('R');print_int(engine_rpm_c);
	//print_char('L');print_long(inj_start_time);
	timer0_ovf = inj_start_time / 256;
	OCR0A = inj_start_time - timer0_ovf * 256;
	if (timer0_ovf > 0){ // Turn on overflow interrupt
		TIMSK0 |= (1 << TOIE0);
	}
	else {
		TIMSK0 |= (1 << OCIE0A);
	}

	uint8_t VE_inter = (((long)VE[lowMAPindex][lowRPMindexInj] * (100 - p_inj) * (100 - q)) +
				((long)VE[lowMAPindex][highRPMindexInj] * p_inj * (100 - q)) +
				((long)VE[highMAPindex][lowRPMindexInj] * (100 - p_inj) * q) +
				((long)VE[highMAPindex][highRPMindexInj] * p_inj * q)) / 10000;
	uint8_t AFR_inter = (((long)AFR[lowMAPindex][lowRPMindexInj] * (100 - p_inj) * (100 - q)) +
			((long)AFR[lowMAPindex][highRPMindexInj] * p_inj * (100 - q)) +
			((long)AFR[highMAPindex][lowRPMindexInj] * (100 - p_inj) * q) +
			((long)AFR[highMAPindex][highRPMindexInj] * p_inj * q)) / 100000;
	// Mass of air = VE * MAP (Pa) * Cyl_disp(M^3) / ( 287 (J/kgK) * (273.15 + IAT(°C))
	//print_char('V'); print_int(VE_inter);
	//print_char('M'); print_int(engine_MAP);
	//print_char('I'); print_int(engine_iat);
	//print_char('A'); print_int(AFR_inter);
	uint32_t M_fuel  = ((long)VE_inter * engine_MAP * ENGINE_CC * 10) / ((long)287 * (273 + engine_iat) * AFR_inter); // Mass of fuel in milligramms
	//uint32_t M_= M_air * 10 / AFR_inter;
	//print_long(M_fuel);
	uint8_t PW = ((long)M_fuel * 1000000 / ((long)INJ_SIZE * PULSE_DIVIDE * NR_OF_INJ_PER_CYL) + INJECTOR_OPENING_TIME) / TIMER0_US_CONST;
	//print_char('P'); print_int(PW);
	OCR0B = PW;



	// Measure analog values on all channels from wideband pin
	startADC();
}

ISR(TIMER0_COMPA_vect)
{
	/*if (counter + TCNT0 >= inj_start_time && inj_flag)
	{
		PORTD ^= (1 << PIND6);
		PORTD ^= (1 << PIND5);
		inj_flag = false;
	}*/
	//print_char('A');print_int(timer0_ovf);
	//print_char('A');
	if (engine_inj && !timer0_ovf){
		PORTD |= (1 << PIND6);
		PORTD |= (1 << PIND5);
		TCNT0 = 0;
		TIMSK0 = (1 << OCIE0B);
	}
}
ISR(TIMER0_COMPB_vect)
{
	//print_char('B');

	if (TCNT0 >= OCR0B){
		PORTD &= ~(1 << PIND6);
		PORTD &= ~(1 << PIND5);
		TIMSK0 = 0;
		//new_line();
	}
	//print_int(OCR0B);
	//print_int(TCNT0);

}
ISR(TIMER0_OVF_vect)
{
	//counter = counter + 256;
	if (--timer0_ovf < 1)
		TIMSK0 = (1 << OCIE0A);
	//print_char('O');
}
