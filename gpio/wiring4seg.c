#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

#define PA 2
#define PB 4
#define PC 1
#define PD 16
#define PE 15
#define PF 8
#define PG 9
#define PDEC 0
#define PDP1 22
#define PDP2 23
#define PDP3 24
#define PDP4 25

// for anode display
char nums[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};
// Wpi pin numbers
char pins[8] = {PA, PB, PC, PD, PE, PF, PG, PDEC};
char pindps[4] = {PDP1, PDP2, PDP3, PDP4};
void clear_pin ()
{
  int i;
  for (i = 0; i < 8; i++)
      digitalWrite(pins[i], 1);
  for (i=0; i < 4; i++)
      digitalWrite(pindps[i], 0);
}
void set_pin (int n)
{
  int i;
  for (i = 0; i < 8; i++)
      digitalWrite(pins[i], (nums[n] >> i) & 0x1);
}

void init_pin ()
{
  int i;
  for (i = 0; i < 8; i++)
      pinMode(pins[i], OUTPUT);
  for (i = 0; i < 4; i++)
      pinMode(pindps[i], OUTPUT);
}
int main(void)
{
  int i;
  wiringPiSetup( );
  init_pin ();
  for (i=0; i < 4; i++)
  {
      clear_pin();
      digitalWrite(pindps[i], 1); /* Choose only one display pin */
      set_pin (i+1);
      delay(1000);
  }
  return 0;
}