/* ATTiny Sound Generator Test sketch for Arduino Due
*
* Created: 31.07.2017 11:14:31
* Author : Tomasz Jaworski
* Modified: 20.08.2017 16:36:18
* Author: Sebastian Bąkała
*
* ATTiny Sound Generator v0.8
*/

#include <playSound.h>


void soundInit(void)
{
	pinMode(SOUND_DATA, OUTPUT);
	pinMode(SOUND_CLOCK, OUTPUT);

	digitalWrite(SOUND_CLOCK, 0);
	digitalWrite(SOUND_DATA, 0);
	delay(1);
}

void sound(int32_t freq, uint8_t tempo)
{
	// przelicz wartosc
	/*
	*  1   1 8MHz 1
	* ---- - ---- -
	* freq 2  8   2
	*/

	//for not dividing by '0'
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
		delayMicroseconds(tempo*1000000);
		digitalWrite(SOUND_CLOCK, 0);
	}
}

void noSound(void)
{
	sound(0); //popraw
}

void playSound(const char *melody)
{
	uint32_t lenOfMelody = strlen(melody), i = 1;
	uint8_t tempo = 0;

	if (lenOfMelody)
	{
		if (melody[0] == 'T' || melody[0] == 't')	//read tempo
		{
			while (isdigit(melody))
			{
				tempo *= 10;
				tempo += /*popraw*/melody++ - 48;

				if (tempo > 255)
				{
					tempo = 255;
					if (i + 1 < lenOfMelody)
						++melody;
					else
						return;	//error
					break;
				}

				++i;
			}
			if (tempo < 32)
			{
				if (tempo == 0)
					tempo = 150;
				else
					tempo = 32;
			}
		}

		for (; i < lenOfMelody; ++i)
		{
			// basic frequency is f0 = A4 = 440Hz
			// a = 1.059463094359
			// formula for frequency of specific note is given by following equation:
			// fn = f0 * (a)^n, where n is a distance from A4 to note given by user

			// list of notes C, C#, D, D#, E, F, F#, G, G#, A, A#, B, <- 12 elements
			// every octave starts from C
			//uint1_t notes[12] = {-9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2}; //
			const int8_t tableOfNotes[] = { 0, 2, -9, -7, -5, -4, -2 };
			uint8_t tableOfNotes_index = 0; //A
			uint8_t note = 65;	//A in ASCII
			int8_t defaultOctave = -4;
			uint8_t n;
			//uint1_t octave; //it will be an multiplier for our equation

			if (melody[i] >= 65 && melody[i] <= 71 || melody[i] >= 97 && melody[i] <= 103)
			{
				if (melody[i] == note || melody[i] == note + 32) // big or small letter representing a note
				{
					if (i + 1 <= lenOfMelody)
					{
						n = tableOfNOtes[tableOfNotes_index];
						if (melody[i + 1] == 83 || melody[i + 1] == 115)	// means fis '#' (S or s)
						{
							++n;
						}
						else if (isdigit(melody[i + 1]))
						{
							sound((f0 * pow(a, n + 12 * (defaultOctave + melody[i + 1]/*popraw*/)), tempo);
						}
						else
						{
							return;
						}
						++melody;
					}
					else
					{
						return;
					}
				}

				if (i + 1 <= lenOfMelody)
				{
					++melody;
				}
				else
				{
					return;
				}

				++tableOfNotes_index;
				++note;

			}
			else if (melody[i] == 48) //0 -> mean pause
			{
				sound(0, tempo);
			}
		}
	}
}
