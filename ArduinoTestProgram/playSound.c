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

void sound(int16_t freq)
{
  // przelicz wartosc
  /*
  *  1   1 8MHz 1
  * ---- - ---- -
  * freq 2  8   2
  */

  //for not dividing by '0'
  uint16_t value = 0;
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
    delayMicroseconds(100);
    digitalWrite(SOUND_CLOCK, 0);
  }
}

void noSound(void)
{
  sound(0);
}

uint1_t Tempo(uint32_t *externalIterator, const char *melody, uint32_t lenOfMelody)
{
  // extract specified tempo
  // !WARNING! tempo_max is 255
  // default tempo is 150
  uint8_t tempo = 150, i = 1, j = 1, multiplier = 100;

  //checking how many numbers defines the tempo
  while(i < lenOfMelody && melody[i] >= 48 && melody[i] <= 57)
  {
    ++i;
    //if more than 3 then its bigger than 255 for sure.
    if (i > 3)
    {
      //so return default value
      return tempo;
    }
  }

  if (i != 1) //true gddy user isn't a troll ;]
  {
    // '0' at the begining? ohhh This is BAAAADDDD... Release The Dragon!'
    melody[1] == 48 ? return tempo : false;
    if (i == 4) //security against nubmers biggest than 255
    {
      uint8_t ___tempoTemp___ = 0;
      ___tempoTemp___ += melody[j] - 48;
      if(___tempoTemp___ > 2) // given number are bigger than 255
      {
        return tempo; //so return default tempo
      }
      if(___tempoTemp___ == 2) //check the other numbers
      {
        ___tempoTemp___ += melody[j+1] - 48;
        if (___tempoTemp___ > 7) //given number is bigger than 255
        {
          return tempo; //so return default tempo
        }
        else if (___tempoTemp___ == 7)
        {
          ___tempoTemp___ += melody[j+2] - 48;
          if (___tempoTemp___ > 13) //given number is bigger than 255
          {
            return tempo; //so return default tempo
          }
          else if (___tempoTemp___ == 13)
          {
            *externalIterator = 3;
            return 255; //tempo_max
          }
        }
      }
    } // maybe its paranoid, maybe it can be protected in a simpler way... dunno... yet

  	if (i == 3)
  	{
  		multiplier /= 10;
  	}

  	if (i == 2)
  	{
  		multiplier /= 100;
  	}

    tempo = 0;
    for(; j < i; ++i, multiplier /= 10, ++(*externalIterator))
    {
      tempo += (melody[j] - 48) * multiplier; //convert 'text type' tempo to intiger
    }
  }
  return tempo;
}

void playSound(const char *melody)
{
  //in case the array was empty im not dividing by sizeof(melody[0])
  uint32_t lenOfMelody = (uint32_t)(sizeof(melody) / sizeof(char)), i = 1;
  uint8_t tempo;

  if (lenOfMelody)
  {
    //if melody[0] == 'T' -> call the 'Tempo' function)
    if (melody[0] == 'T')
    {
      tempo = Tempo(&i, melody, lenOfMelody);
    }
    //if not, tempo = 150 (default value)
    for(; i < lenOfMelody; ++i)
    {
      // basic frequency is f0 = A4 = 440Hz
      // a = 1.059463094359
      // formula for frequency of specific note is given by following equation:
      // fn = f0 * (a)^n, where n is a distance from A4 to note given by user

      // list of notes C, C#, D, D#, E, F, F#, G, G#, A, A#, B, <- 12 elements
      // every octave starts from C
      //uint1_t notes[12] = {-9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2}; //
      uint1_t octave; //it will be an multiplier for our equation

      switch (melody[i])
      {
        case 67: //C
        {
          if (i+1 < lenOfMelody)
          {
            if (melody[i+1] == 83) // CS <- C#
            {

            }
          }
        }
      }

      if(melody[i] == 48) //0 -> mean pause
      {
        noSound(0);
      }

      delay(tempo);
    }
  }
}
