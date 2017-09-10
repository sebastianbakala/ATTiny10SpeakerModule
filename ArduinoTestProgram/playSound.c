/* ATTiny Sound Generator Test sketch for Arduino Due
*
* Created: 31.07.2017 11:14:31
* Author : Tomasz Jaworski
* Modified: 09.09.2017 21:14:38
* Author: Sebastian Bąkała
*
* ATTiny Sound Generator v0.8
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "playSound.h"


void soundInit(void)
{
	pinMode(SOUND_DATA, OUTPUT);
	pinMode(SOUND_CLOCK, OUTPUT);

	digitalWrite(SOUND_CLOCK, 0);
	digitalWrite(SOUND_DATA, 0);
	delay(1);
}

void sound(uint16_t freq, uint8_t tempo)
{
	// przelicz wartosc
	/*
	*  1   1 8MHz 1
	* ---- - ---- -
	* freq 2  8   2
	*/

	uint32_t value = 0;
	if (freq)
	{
		value = 250000L / freq;
	}

	for (int i = 0; i < 16; i++)
	{
		digitalWrite(SOUND_DATA, value & 0x8000);
		value <<= 1;

		// pulse the data
		digitalWrite(SOUND_CLOCK, 1);
		delayMicroseconds(tempo * 1000000);
		digitalWrite(SOUND_CLOCK, 0);
	}
}

void noSound(uint8_t tempo)
{
	sound(0, tempo);
}

void playSound(const char *melody)
{
	if (!strlen(melody) || melody == NULL)
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

		if (*melody >= 'A' && *melody <= 'G' || *melody >= 'a' && *melody <= 'g' || *melody == 'S' || *melody == 's')
		{
			if (*melody == note || *melody == note + 32)
			{
				n = tableOfNotes[tableOfNotes_index];
			loop:
				if (*(melody + 1))
				{
					if ((*(melody + 1) == 'S' || *(melody + 1) == 's') && (*melody == 'A' || *melody == 'a' || *melody == 'C' || *melody == 'c' || *melody == 'D' || *melody == 'd' || *melody == 'F' || *melody == 'f' || *melody == 'G' || *melody == 'g'))	//S or s means fis '#'
					{
						// only A, C, D, F, G notes has # (fis)
						while (*(melody + 1) == 'S' || *(melody + 1) == 's') ++melody;
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
						sound((uint16_t)round(f0 * pow(a, n + 12 * (defaultOctave + octave))), (uint32_t)tempo * 1000000);
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

		else if (*melody == 'P' || *melody == 'p') //P or p (means pause)
		{
			sound(0, tempo * 1000000);
			if (!(*(++melody)))
				return;
		}
		else if (*melody == 'T' || *melody == 't')
		{
			tempo -= 0;	//nothing for 'sssssssssSSSSSsssSSSSss' <- e.g. sequence
		}
		else
			return;	// bad input sequence
	}
}
