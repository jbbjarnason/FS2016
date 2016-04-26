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
