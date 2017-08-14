#define SOUND_CLOCK  2
#define SOUND_DATA 3

void soundInit(void)
{
  pinMode(SOUND_DATA, OUTPUT);
  pinMode(SOUND_CLOCK, OUTPUT);

  digitalWrite(SOUND_CLOCK, 0);
  digitalWrite(SOUND_DATA, 0);
  delay(1);

}

#define C 261
#define D 294
#define E 330
#define F 349
#define G 392
#define A 440
#define H 494
#define C2 523

int16_t s1[] = 
{
  C, 2, D, 2, E, 2, F, 2,
  G, 1, E, 1,
  G, 1, E, 1, 
  E, 2, E, 2, D, 2, D, 2,
  C, 1,
  0, 0,
};

void sound(int16_t freq)
{
  // przelicz wartosc
  /*
   *  1   1 8MHz 1
   * ---- - ---- -
   * freq 2  8   2
   */

  uint16_t value = 250000L / freq;
  

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


void setup() {
  // put your setup code here, to run once:

  soundInit();
}


void loop() {
  // put your main code here, to run repeatedly:

  for (int i = 0; s1[i] != 0; i += 2)
  {
    sound(s1[i]);
    delay(400/s1[i+1]);
    noSound();
    delay(40);
  }

  noSound();

  delay(4000);
  
}
  

