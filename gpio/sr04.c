#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>


int TRIG = 29; //gpio 21 pin 40
int ECHO = 28; //gpio 20 pin 38

static int Echo_Test()
{
  unsigned long TX_time = 0; // TX: Transmit
  unsigned long RX_time = 0; // RX: Receive
  float distance = 0;       
  unsigned long timeout = 50000000;   // 50*10^6 us == 50s
  unsigned long Wait_time=micros();
  /*
  The micros() function is a built-in function in many microcontroller libraries (e.g., Arduino) that returns the current time in microseconds since the microcontroller started running.
  */
  pinMode(TRIG, OUTPUT); //gpio 21 pin 40 using trigger
  pinMode(ECHO, OUTPUT); //gpio 20 pin 38 using Echo ultra sound

  // Ensure trigger is low.
  digitalWrite(TRIG, LOW);
  delay(50); //mili sec

  // Trigger tx sound.
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  /*
  delayMicroseconds(10);

  After setting the TRIG pin to HIGH, there is a delay of 10 microseconds. The delayMicroseconds function pauses the program's execution for the specified number of microseconds (in this case, 10 microseconds).
  This delay is often necessary to ensure that the triggering signal remains HIGH long enough for the sensor to recognize it and start sending out sound waves. The exact delay duration may vary depending on the sensor's specifications.
  
  digitalWrite(TRIG, LOW);

  Finally, this line sets the TRIG pin back to a LOW voltage level, deactivating the trigger signal.
  The transition from HIGH to LOW may signal the ultrasonic sensor to stop emitting sound waves and prepare for receiving the echo reflected from an object.
  */

  // Wait for tx response, or timeout.
  while((digitalRead(ECHO) == LOW && (micros()-Wait_time) < timeout)){
    if(digitalRead(ECHO) == HIGH) break;
  }

  // Cancel on timeout.
  if ((micros()-Wait_time) > timeout){
    printf("0 Out of range.micros =%d wait-time=%d \n", micros(), Wait_time);
    //return 0;
  }

  TX_time = micros(); //since call wiringPiSetup, the number of microseconds
  //Wait for rx sound response, or timeout.
  while((digitalRead(ECHO) == HIGH && (micros()-Wait_time) < timeout)){
    if(digitalRead(ECHO) == LOW) break;
  }


  if ((micros()-Wait_time) > timeout){
    printf("1.Out of range.\n");
  }

  RX_time = micros();

  distance = (float) (RX_time - TX_time) * 0.017;
  printf("Range %.2f cm.\n", distance);
  return 1;

}


int main()
{
  printf (" HC-SR04 Ultra-sonic distance measure program \n");
  if (wiringPiSetup () == -1) {
    exit(EXIT_FAILURE);
  }
  if (setuid(getuid()) < 0) {
    perror("Dropping privileges failed.\n");
    exit(EXIT_FAILURE);
  }
  for(;;){
    Echo_Test();
    delay(500); //500ms
    //sleep(1);
  }
  return 0;
}