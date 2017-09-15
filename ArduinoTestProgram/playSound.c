/* ATTiny Sound Generator Test sketch for Arduino Due
*
* Created: 31.07.2017 11:14:31
* Author : Tomasz Jaworski
* Modified: 09.09.2017 21:14:38
* Author: Sebastian Bąkała
*
* ATTiny Sound Generator v0.8
*/

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "playSound.h"


//void soundInit(void)
//{
//	pinMode(SOUND_DATA, OUTPUT);
//	pinMode(SOUND_CLOCK, OUTPUT);
//
//	digitalWrite(SOUND_CLOCK, 0);
//	digitalWrite(SOUND_DATA, 0);
//	delay(1);
//}
//
//void sound(uint16_t freq)
//{
//	// przelicz wartosc
//	/*
//	*  1   1 8MHz 1
//	* ---- - ---- -
//	* freq 2  8   2
//	*/
//
//	uint32_t value = 0;
//	if (freq)
//	{
//		value = 250000L / freq;
//	}
//
//	for (int i = 0; i < 16; i++)
//	{
//		digitalWrite(SOUND_DATA, value & 0x8000);
//		value <<= 1;
//
//		// pulse the data
//		digitalWrite(SOUND_CLOCK, 1);
//		delayMicroseconds(100);
//		digitalWrite(SOUND_CLOCK, 0);
//	}
//}
//
//void noSound()
//{
//	sound(0);
//}

void playSound(const char *melody)
{
	if (melody == NULL || !strlen(melody))
		return;

	uint16_t tempo = 0;
	uint8_t tableOfNotes_index = 0;	//A
	uint8_t note = 'A';	//A in ASCII

	while (*melody)
	{

		while (*melody == 'T' || *melody == 't')
		{
			if (isdigit(*(melody + 1)))
				tempo = 0;
			++melody;
		}

		while (isdigit(*melody))
		{
			tempo *= 10;
			tempo += (uint16_t)*melody - 48;

			if (tempo > 255)
			{
				tempo = 255;
				if (*(melody + 1))
					++melody;
				else
					return;	//error
				break;
			}
			++melody;
		}

		if (tempo < 32)
		{
			if (tempo == 0)
				tempo = 150;
			else
				tempo = 32;
		}

		const int8_t tableOfNotes[] = { 0, 2, -9, -7, -5, -4, -2 };
		int8_t defaultOctave = -4, n;
		uint8_t octave = 0;

		if (UPPER(*melody) >= 'A' && UPPER(*melody) <= 'G' || UPPER(*melody) == 'S')
		{
			if (UPPER(*melody) == note)
			{
				n = tableOfNotes[tableOfNotes_index];
			loop:
				if (*(melody + 1))
				{
					if ((UPPER(*(melody + 1)) == 'S') && (UPPER(*melody) == 'A' || UPPER(*melody) == 'C' || UPPER(*melody) == 'D' || UPPER(*melody) == 'F' || UPPER(*melody) == 'G'))	//S or s means fis '#'
					{
						// only A, C, D, F, G notes has # (fis)
						while (UPPER(*(melody + 1)) == 'S') ++melody;
						++n;
						goto loop;
					}
					else if (isdigit(*(melody + 1)))
					{
						while (isdigit(*(++melody)) && *melody)
						{
							octave *= 10;
							octave += (uint16_t)*melody - 48;
							if (octave > 8)
								return; //max octave is 8
						}
						//sound((uint16_t)round(f0 * pow(a, n + 12 * (defaultOctave + octave))));
						printf("tempo = %d\n", tempo);
						printf("freq = %u\n", (uint16_t)round(f0 * pow(a, n + 12 * (defaultOctave + octave))));
						//delay(round(60000 / tempo));
					}
					else
						return;	//bad input sequence
				}
				else
					return;
			}

			++note;
			if (++tableOfNotes_index > 6)
			{
				tableOfNotes_index = 0;
				note = 65;
			}
		}

		else if (UPPER(*melody) == 'P') //P or p (means pause)
		{
			//sound(0);
			//delay(round(60000 / tempo));
			if (!(*(++melody)))
				return;
		}
		else if (UPPER(*melody) == 'T')
		{
			tempo -= 0;	//nothing for 'sssssssssSSSSSsssSSSSss' <- e.g. sequence
		}
		else
			return;	// bad input sequence
	}
}

int main(void)
{
	char melody[] = { "T250CS2C2CS2C2cs2T125PPT250c2c3c3c3e3Ds2" };
	playSound(melody);
	system("PAUSE");

	return 0;
}
