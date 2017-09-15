/* ATTiny Sound Generator Test sketch for Arduino Due

* Created: 31.07.2017 11:14:31
* Author : Tomasz Jaworski
* Modified: 09.09.2017 21:14:38
* Author: Sebastian Bąkała

* ATTiny Sound Generator v0.8
*/

#ifndef SOUND_CLOCK
	#define SOUND_CLOCK 2
	#define SOUND_DATA 3
	#define f0 440 //Hz
	#define a 1.059463094359 //2^(1/12)
	#define UPPER(__x) (((__x) >= 'a' && (__x) <= 'z') ? ((__x) - 32) : (__x))

	void soundInit(void);
	void sound(uint16_t);
	void noSound();
	void playSound(const char *);
#endif
