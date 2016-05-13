/*
 * sensors.c
 *
 *  Created on: 8. ma� 2016
 *      Author: JonB
 */

#include "sensors.h"

int8_t manifoldTemp(int8_t index)
{
	static const int8_t lookup[256] = {
		 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
		 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
		 0,   0,   0,   0,   0, 108, 103, 101,  99,  96,  95,  91,
		91,  89,  88,  87,  86,  85,  84,  83,  83,  81,  80,  79,
		79,  78,  78,  77,  76,  75,  75,  74,  74,  73,  72,  71,
		70,  69,  67,  67,  67,  66,  66,  65,  64,  64,  63,  62,
		61,  61,  61,  60,  60,  59,  59,  58,  58,  57,  56,  56,
		55,  55,  55,  55,  54,  53,  53,  52,  52,  51,  51,  50,
		50,  49,  49,  49,  48,  48,  47,  47,  46,  46,  46,  45,
		45,  44,  44,  43,  43,  43,  42,  42,  41,  41,  40,  40,
		40,  39,  39,  38,  38,  38,  37,  37,  36,  36,  36,  35,
		35,  34,  34,  34,  33,  33,  32,  32,  32,  31,  31,  31,
		30,  30,  29,  29,  29,  28,  28,  27,  27,  27,  26,  26,
		25,  25,  25,  24,  24,  23,  23,  23,  22,  22,  21,  21,
		21,  20,  20,  20,  19,  19,  18,  18,  18,  17,  17,  16,
		16,  15,  15,  15,  15,  14,  14,  13,  13,  13,  12,  12,
		11,  11,  10,  10,  10,  -1,  -2,  -2,  -3,  -3,  -4,  -5,
		-5,  -6,  -7,  -8,  -9, -10, -10,   0,   0,   0,   0,   0,
		 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
		 0,   0,   0,   0,   0,   0,   0,   0,   0};

	return lookup[index];
}