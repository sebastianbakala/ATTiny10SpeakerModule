/*
 * ATTiny Sound Generator Test sketch for Arduino Due
 *
 * Created: 31.07.2017 11:14:31
 * Author : Tomasz Jaworski
 */

#include playSound.h



int16_t s1[] =
{
  C, 2, D, 2, E, 2, F, 2,
  G, 1, E, 1,
  G, 1, E, 1,
  E, 2, E, 2, D, 2, D, 2,
  C, 1,
  0, 0,
};






void setup() {
  // put your setup code here, to run once:

  soundInit();
}


void loop()
{
  // taken from http://www.elektroda.pl/rtvforum/topic1812254.html

  sound (440);
  delay (150);
  sound (440);
  delay (150);
  sound (262);
  delay (150);
  sound (440);
  delay (150);
  sound (294);
  delay (150);
  sound (440);
  delay (150);
  sound (330);
  delay (150);
  sound (294);
  delay (150);
  sound (262);
  delay (150);
  sound (262);
  delay (150);
  sound (330);
  delay (150);
  sound (262);
  delay (150);
  sound (392);
  delay (150);
  sound (262);
  delay (150);
  sound (330);
  delay (150);
  sound (262);
  delay (150);
  sound (392);
  delay (150);
  sound (392);
  delay (150);
  sound (494);
  delay (150);
  sound (392);
  delay (150);
  sound (262);
  delay (150);
  sound (392);
  delay (150);
  sound (294);
  delay (150);
  sound (262);
  delay (150);
  sound (349);
  delay (150);
  sound (349);
  delay (150);
  sound (440);
  delay (150);
  sound (349);
  delay (150);
  sound (262);
  delay (150);
  sound (349);
  delay (150);
  sound (494);
  delay (150);
  sound (262);
  delay (150);
  //druga zwrotka
  sound (440);
  delay (150);
  sound (440);
  delay (150);
  sound (262);
  delay (150);
  sound (440);
  delay (150);
  sound (294);
  delay (150);
  sound (440);
  delay (150);
  sound (330);
  delay (150);
  sound (294);
  delay (150);
  sound (262);
  delay (150);
  sound (262);
  delay (150);
  sound (330);
  delay (150);
  sound (262);
  delay (150);
  sound (392);
  delay (150);
  sound (262);
  delay (150);
  sound (330);
  delay (150);
  sound (262);
  delay (150);
  sound (392);
  delay (150);
  sound (392);
  delay (150);
  sound (494);
  delay (150);
  sound (392);
  delay (150);
  sound (262);
  delay (150);
  sound (392);
  delay (150);
  sound (294);
  delay (150);
  sound (262);
  delay (150);
  sound (349);
  delay (150);
  sound (349);
  delay (150);
  sound (440);
  delay (150);
  sound (349);
  delay (150);
  sound (262);
  delay (150);
  sound (349);
  delay (150);
  sound (494);
  delay (150);
  sound (262);
  delay (150);

  //{refren}
  sound (440);
  delay (150);
  sound (440);
  delay (150);
  sound (440);
  delay (150);
  sound (440);
  delay (150);
  sound (392);
  delay (150);
  sound (262);
  delay (150);

  sound (440);
  delay (150);
  sound (440);
  delay (150);
  sound (440);
  delay (150);
  sound (440);
  delay (150);
  sound (392);
  delay (150);
  sound (330);
  delay (150);

  sound (440);
  delay (150);
  sound (440);
  delay (150);
  sound (440);
  delay (150);
  sound (440);
  delay (150);
  sound (392);
  delay (150);
  sound (262);
  delay (150);
  sound (440);
  delay (150);
  sound (440);
  delay (150);
  sound (440);
  delay (150);
  sound (440);
  delay (150);
  sound (440);
  delay (150);
  sound (440);
  delay (150);
  sound (440);
  delay (150);

  sound (440);
  delay (150);
  sound (440);
  delay (150);
  sound (440);
  delay (150);
  sound (440);
  delay (150);
  sound (392);
  delay (150);
  sound (262);
  delay (150);
  sound (440);
  delay (150);
  sound (440);
  delay (150);
  sound (440);
  delay (150);


}

void loop1() {
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
