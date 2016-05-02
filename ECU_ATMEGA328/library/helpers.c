/*
 * helpers.c
 *
 *  Created on: 25. apr. 2016
 *      Author: JonB
 */
#include "helpers.h"



// Calculate the weight of the value compared to indexes x1 and x2
uint8_t interpolation(uint16_t value, uint16_t x1, uint16_t x2)
{
	if (value <= x1) // below or equal to lower bound
		return 0;

	if (value >= x2) // above or equal to upper bounds
		return 100;

	return ((long)(value - x1) * 100)/((x2 - x1));
}

/*uint8_t average(uint8_t vector[], uint8_t length)
{
	uint16_t summ = 0;
	for (uint8_t i = 0; i < length; i++)
		summ += vector[i];
	return summ / length;
}*/

uint8_t median(uint8_t array[], uint8_t length)
{
	// insertion sort
	uint8_t d, c, t;
	for (c = 1; c < length; c++) {
		d = c;
		while (d > 0 && array[d] < array[d - 1]) {
			t = array[d];
			array[d] = array[d-1];
			array[d-1] = t;
			d--;
		}
	}
	// return median
	return array[length / 2];
}

uint16_t lookup_table(uint16_t table[], uint8_t max_length, uint16_t compare)
{
	uint8_t lowindex = 0;
	uint8_t highindex = max_length - 1;
	for (uint8_t Index = 0; Index < max_length; Index++)
	{
		if (table[Index] > compare) {
			lowindex = Index;
		} else if (table[Index] < compare) {
			highindex = Index;
			break;
		} else if (table[Index] == compare) {
			lowindex = Index;
			highindex = Index;
			break;
		}
	}
	return lowindex | (highindex << 8);
}

void print_serial()
{
	print_ser++;
	if (print_ser == 1)
		print_load_indexes();
	else if (print_ser == 2)
		print_injection_indexes();
	else if (print_ser == 3)
		print_ignition_indexes();
	else if (print_ser == 4)
		print_interpolation();
	else if (print_ser == 5)
		print_Analog_1();
	else if (print_ser == 6)
		print_Analog_2();
	else if (print_ser == 7)
		print_RPM();
	else if (print_ser > 7)
		print_ser = 0;
}
void print_load_indexes()
{
	print_char('L');print_char(' ');
	print_byte(lowMAPindex);print_char(' ');
	print_byte(highMAPindex);
	new_line();
}
void print_injection_indexes()
{
	print_char('I');print_char(' ');
	print_byte(lowRPMindexInj);print_char(' ');
	print_byte(highRPMindexInj);
	new_line();
}
void print_ignition_indexes()
{
	print_char('S');print_char(' ');
	print_byte(lowRPMindexIgn);print_char(' ');
	print_byte(highRPMindexIgn);
	new_line();
}
void print_interpolation()
{
	print_char('P');print_char(' ');
	print_byte(p_inj);print_char(' ');
	print_byte(p_ign);print_char(' ');
	print_byte(q);
	new_line();
}
void print_Analog_1()
{
	print_char('A');print_char(' ');
	print_byte(sensor_reading[WB_PIN]);print_char(' ');
	print_byte(sensor_reading[IAT_PIN]);print_char(' ');
	print_byte(sensor_reading[TPS_PIN]);
	new_line();
}
void print_Analog_2()
{
	print_char('a');print_char(' ');
	print_byte(sensor_reading[CLT_PIN]);print_char(' ');
	print_byte(sensor_reading[MAP2_PIN]);print_char(' ');
	//print_byte(sensor_reading[OT_PIN]);print_char(' ');
	print_byte(engine_MAP);
	new_line();
}
void print_RPM()
{
	print_char('R');print_char(' ');
	print_int(engine_rpm_c);
	//new_line();
}
