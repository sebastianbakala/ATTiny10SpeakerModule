 /* ATTiny Sound Generator Test sketch for Arduino Due
  * Created: 31.07.2017 11:14:31
  * Author : Tomasz Jaworski
  * Modified: 20.08.2017 16:36:18
  * Author: Sebastian Bąkała
  * ATTiny Sound Generator v0.8
  */

#ifndef SOUND_CLOCK
#define SOUND_CLOCK

  #define SOUND_CLOCK 2
  #define SOUND_DATA 3
  #define A4 440 //Hz
  #define a 1.059463094359 //2^(1/12)

  void soundInit(void);
  void sound(int16_t);
  void noSound(void);
  uint8_t Tempo(uint32_t, const char *, uint32_t);
  void playSound(const char *);

#endif
