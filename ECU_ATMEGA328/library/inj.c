

#include "inj.h"

void initInjTable()
{
	// Initialize load vector
	LOAD[0] = 25;LOAD[1] = 46;LOAD[2] = 66;LOAD[3] = 87;LOAD[4] = 108;LOAD[5] = 128;LOAD[6] = 149;LOAD[7] = 170;
	// athuga load vector � generator, hann er a�eins ��ruv�si
	// Initializing Volumetric efficiency table
	VE[7][0] = 50; VE[7][1] = 50; VE[7][2] = 85; VE[7][3] = 120; VE[7][4] = 140; VE[7][5] = 170; VE[7][6] = 200; VE[7][7] = 200;
	VE[6][0] = 50; VE[6][1] = 50; VE[6][2] = 80; VE[6][3] = 100; VE[6][4] = 132; VE[6][5] = 160; VE[6][6] = 190; VE[6][7] = 190;
	VE[5][0] = 50; VE[5][1] = 50; VE[5][2] = 65; VE[5][3] = 80; VE[5][4] = 115; VE[5][5] = 135; VE[5][6] = 139; VE[5][7] = 143;
	VE[4][0] = 50; VE[4][1] = 50; VE[4][2] = 60; VE[4][3] = 80; VE[4][4] = 100; VE[4][5] = 102; VE[4][6] = 106; VE[4][7] = 111;
	VE[3][0] = 50; VE[3][1] = 50; VE[3][2] = 55; VE[3][3] = 70; VE[3][4] = 109; VE[3][5] = 94; VE[3][6] = 89; VE[3][7] = 84;
	VE[2][0] = 50; VE[2][1] = 50; VE[2][2] = 50; VE[2][3] = 60; VE[2][4] = 101; VE[2][5] = 96; VE[2][6] = 81; VE[2][7] = 76;
	VE[1][0] = 50; VE[1][1] = 50; VE[1][2] = 50; VE[1][3] = 50; VE[1][4] = 91; VE[1][5] = 86; VE[1][6] = 72; VE[1][7] = 68;
	VE[0][0] = 50; VE[0][1] = 50; VE[0][2] = 50; VE[0][3] = 50; VE[0][4] = 84; VE[0][5] = 80; VE[0][6] = 66; VE[0][7] = 62;
	// Initialize Air to fuel ratio table
	//AFR[7][0] = 128; AFR[7][1] = 128; AFR[7][2] = 112; AFR[7][3] = 112; AFR[7][4] = 112; AFR[7][5] = 106; AFR[7][6] = 106; AFR[7][7] = 106;
	//AFR[6][0] = 128; AFR[6][1] = 128; AFR[6][2] = 116; AFR[6][3] = 116; AFR[6][4] = 116; AFR[6][5] = 110; AFR[6][6] = 110; AFR[6][7] = 110;
	//AFR[5][0] = 128; AFR[5][1] = 128; AFR[5][2] = 120; AFR[5][3] = 120; AFR[5][4] = 120; AFR[5][5] = 114; AFR[5][6] = 114; AFR[5][7] = 114;
	//AFR[4][0] = 128; AFR[4][1] = 128; AFR[4][2] = 124; AFR[4][3] = 124; AFR[4][4] = 124; AFR[4][5] = 118; AFR[4][6] = 118; AFR[4][7] = 118;
	//AFR[3][0] = 128; AFR[3][1] = 128; AFR[3][2] = 128; AFR[3][3] = 128; AFR[3][4] = 128; AFR[3][5] = 122; AFR[3][6] = 122; AFR[3][7] = 122;
	//AFR[2][0] = 128; AFR[2][1] = 128; AFR[2][2] = 133; AFR[2][3] = 133; AFR[2][4] = 133; AFR[2][5] = 127; AFR[2][6] = 127; AFR[2][7] = 127;
	//AFR[1][0] = 128; AFR[1][1] = 128; AFR[1][2] = 137; AFR[1][3] = 137; AFR[1][4] = 137; AFR[1][5] = 131; AFR[1][6] = 131; AFR[1][7] = 131;
	//AFR[0][0] = 128; AFR[0][1] = 128; AFR[0][2] = 141; AFR[0][3] = 141; AFR[0][4] = 141; AFR[0][5] = 135; AFR[0][6] = 135; AFR[0][7] = 135;
	AFR[7][0] = 79; AFR[7][1] = 79; AFR[7][2] = 63; AFR[7][3] = 63; AFR[7][4] = 63; AFR[7][5] = 57; AFR[7][6] = 57; AFR[7][7] = 57;
	AFR[6][0] = 79; AFR[6][1] = 79; AFR[6][2] = 67; AFR[6][3] = 67; AFR[6][4] = 67; AFR[6][5] = 61; AFR[6][6] = 61; AFR[6][7] = 61;
	AFR[5][0] = 79; AFR[5][1] = 79; AFR[5][2] = 71; AFR[5][3] = 71; AFR[5][4] = 71; AFR[5][5] = 65; AFR[5][6] = 65; AFR[5][7] = 65;
	AFR[4][0] = 79; AFR[4][1] = 79; AFR[4][2] = 75; AFR[4][3] = 75; AFR[4][4] = 75; AFR[4][5] = 69; AFR[4][6] = 69; AFR[4][7] = 69;
	AFR[3][0] = 79; AFR[3][1] = 79; AFR[3][2] = 79; AFR[3][3] = 79; AFR[3][4] = 79; AFR[3][5] = 73; AFR[3][6] = 73; AFR[3][7] = 73;
	AFR[2][0] = 79; AFR[2][1] = 79; AFR[2][2] = 84; AFR[2][3] = 84; AFR[2][4] = 84; AFR[2][5] = 78; AFR[2][6] = 78; AFR[2][7] = 78;
	AFR[1][0] = 79; AFR[1][1] = 79; AFR[1][2] = 88; AFR[1][3] = 88; AFR[1][4] = 88; AFR[1][5] = 82; AFR[1][6] = 82; AFR[1][7] = 82;
	AFR[0][0] = 79; AFR[0][1] = 79; AFR[0][2] = 92; AFR[0][3] = 92; AFR[0][4] = 92; AFR[0][5] = 86; AFR[0][6] = 86; AFR[0][7] = 86;
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

	// Initialize RPM vector
	uint8_t temp_rpm[MAX_RPM_TABLE_LENGTH] = {15, 20, 32, 44, 56, 67, 79, 91}; // temporary rpm vector, expressed in RPM / 100
	for (uint8_t i = 0; i < MAX_RPM_TABLE_LENGTH; i++){
		RPM_INJ_C[i] = 600000 / ((long)temp_rpm[i] * TIMER1_US_CONST);
		print_string("INJ_RPM"); print_int(temp_rpm[i]);
		for (uint8_t j = 0; j < MAX_LOAD_TABLE_LENGTH; j++){
			print_string("VE"); print_int(VE[i][j]);
			print_string("AFR"); print_int(AFR[i][j]);
		}
		print_string("VE_Done"); new_line();
		print_string("AFR_Done"); new_line();
	}
}

void initInjection()
{
	// Turn off global interrupts
	cli();
	// Initialize Mapping tables
	initInjTable();
	// Initialize TIMER0
	// Prescale timer to 16 MHz / 128, 64 �s per count
	TCCR0B = (1 << CS00) | (1 << CS02);
	// Enable compare match a, b and overflow
	//TIMSK0 = (1 << TOIE0);
	//TIMSK0 = (1 << OCIE0A) | (1 << OCIE0B) | (1 << TOIE0);
	TIMSK0 = (1 << OCIE0B);
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
	ovf_flag = false;
	stop_flag = false;
	timer0_ovf = 0;
	timer1_counts = 0;
	sei();
}
ISR(INT0_vect)
{
	startADC();
}
void startINJ()
{
	// Check Rev limit
	if (engine_rpm_c < REV_LIMIT_COUNTS){
		engine_inj = false;
	}
	// Fuel cut hysterisis
	if (!engine_inj){
		if (engine_rpm_c > FUEL_CUT_RPM_COUNTS){
			engine_inj = true;
		}
		else
			return;
	}

	// Fuel CUTT
	if(engine_inj ){//&& dec_cut){
		PORTD |= (1 << PIND6);
		PORTD |= (1 << PIND5);
	} else {
		PORTD &= ~(1 << PIND6);
		PORTD &= ~(1 << PIND5);
	}
	/*uint8_t VE_inter = (((long)VE[lowMAPindex][lowRPMindexInj] * (100 - p_inj) * (100 - q)) +
					((long)VE[lowMAPindex][highRPMindexInj] * p_inj * (100 - q)) +
					((long)VE[highMAPindex][lowRPMindexInj] * (100 - p_inj) * q) +
					((long)VE[highMAPindex][highRPMindexInj] * p_inj * q)) / 10000;
	uint16_t AFR_inter = (((long)AFR[lowMAPindex][lowRPMindexInj] * (100 - p_inj) * (100 - q)) +
			((long)AFR[lowMAPindex][highRPMindexInj] * p_inj * (100 - q)) +
			((long)AFR[highMAPindex][lowRPMindexInj] * (100 - p_inj) * q) +
			((long)AFR[highMAPindex][highRPMindexInj] * p_inj * q)) / 1000;*/


	//M_fuel1 = ((unsigned long)VE_inter * engine_MAP * FUEL_CONST) / ((unsigned long) AFR_inter * (273 + engine_iat));
	//inj_stop_time = (M_fuel1 + INJECTOR_OPENING_TIME + accel_enrich) / TIMER0_US_CONST;

	TCNT0 = 0;
	OCR0B = inj_stop_time;
}
ISR(TIMER0_COMPB_vect)
{
	if(TCNT0 >= OCR0B){
		PORTD &= ~(1 << PIND6);
		PORTD &= ~(1 << PIND5);
	}
}
// Calculate injector timing
/*ISR(INT0_vect) // Interrupts 2� after TDC
{
	TCNT0 = 0;
	//counter = 0;
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
		ovf_flag = false;
	}
	else {
		TIMSK0 |= (1 << OCIE0A);
	}

	uint8_t VE_inter = (((long)VE[lowMAPindex][lowRPMindexInj] * (100 - p_inj) * (100 - q)) +
				((long)VE[lowMAPindex][highRPMindexInj] * p_inj * (100 - q)) +
				((long)VE[highMAPindex][lowRPMindexInj] * (100 - p_inj) * q) +
				((long)VE[highMAPindex][highRPMindexInj] * p_inj * q)) / 10000;
	uint16_t AFR_inter = (((long)AFR[lowMAPindex][lowRPMindexInj] * (100 - p_inj) * (100 - q)) +
			((long)AFR[lowMAPindex][highRPMindexInj] * p_inj * (100 - q)) +
			((long)AFR[highMAPindex][lowRPMindexInj] * (100 - p_inj) * q) +
			((long)AFR[highMAPindex][highRPMindexInj] * p_inj * q)) / 1000;
	// Mass of air = VE * MAP (Pa) * Cyl_disp(M^3) / ( 287 (J/kgK) * (273.15 + IAT(�C))
	//print_char('V'); print_int(VE_inter);
	//print_char('M'); print_int(engine_MAP);
	//print_char('I'); print_int(engine_iat);
	//print_char('A'); print_int(AFR_inter);
	//uint32_t M_fuel  = ((long)VE_inter * engine_MAP * ENGINE_CC * 10) / ((long)287 * (273 + engine_iat) * AFR_inter * 1.1); // Mass of fuel in milligramms
	//uint32_t M_= M_air * 10 / AFR_inter;
	//print_long(M_fuel);
	//uint8_t PW = ((long)M_fuel * 1000000 / ((long)INJ_SIZE * PULSE_DIVIDE * NR_OF_INJ_PER_CYL) + INJECTOR_OPENING_TIME) / TIMER0_US_CONST;
	//print_char('P'); print_int(PW);
	//OCR0B = PW;

	M_fuel1 = ((unsigned long)VE_inter * engine_MAP * FUEL_CONST) / ((unsigned long) AFR_inter * (273 + engine_iat));
	inj_stop_time = (M_fuel1 + INJECTOR_OPENING_TIME + accel_enrich) / TIMER0_US_CONST;
	uint16_t cycle = ((long)engine_rpm_c * TIMER1_US_CONST) / TIMER0_US_CONST;
	if (inj_stop_time + inj_start_time > cycle){
		OCR0B = (int)inj_stop_time + inj_start_time - cycle;
		stop_flag = true;
	}
	else{
		OCR0B = inj_stop_time;
		stop_flag = false;
	}

	// Measure analog values on all channels from wideband pin
	startADC();
	timer1_counts = TCNT1;
}

ISR(TIMER0_COMPA_vect)
{
//	if (counter + TCNT0 >= inj_start_time && inj_flag)
//	{
//		PORTD ^= (1 << PIND6);
//		PORTD ^= (1 << PIND5);
//		inj_flag = false;
//	}
	//print_char('A');print_int(timer0_ovf);
	//print_char('A');
	PORTB ^= (1 << PINB4);
	if ((TCNT0 >= OCR0A) && engine_inj && !timer0_ovf){
		PORTD |= (1 << PIND6);
		PORTD |= (1 << PIND5);
		if (!stop_flag)
			TCNT0 = 0;
		TIMSK0 = (1 << OCIE0B);
		engine_inj = false;
	}
}
ISR(TIMER0_COMPB_vect)
{
	//print_char('B');

	if (TCNT0 >= OCR0B){
		PORTD &= ~(1 << PIND6);
		PORTD &= ~(1 << PIND5);
		//TIMSK0 = 0;
		//new_line();
	}
	//print_int(OCR0B);
	//print_int(TCNT0);

}
ISR(TIMER0_OVF_vect)
{

	//counter = counter + 256;
	PORTB ^= (1 << PINB3);
	//if (ovf_flag){
	//	ovf_flag = false;
	//	timer0_ovf--;
	//}
	if (timer1_counts + TIMER0_US_CONST/TIMER1_US_CONST < TCNT1)
		ovf_flag = true;
	if (ovf_flag && (--timer0_ovf < 1))
	{
	//	print_char('h');
		TCNT0 = 0;
		TIMSK0 = (1 << OCIE0A);
	}
	//print_char('O');
}*/
