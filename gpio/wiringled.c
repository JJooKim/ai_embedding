#include <WiringPi.h> // for wiringPi Libraries
#include <stdio.h>
#include <stdlib.h> // for atoi() function


int ledControl(int gpio){

  int i;

  pinMode(gpio, OUTPUT) /* Pin의 출력 설정 */

  for(i = 0; i < 5; i++){
    digitalWrite(gpio, HIGH);
    delay(1000); /* 1초(1000밀리초) 동안 대기*/
    digitalWrite(gpio, LOW);
    delay(1000);
  }

  return 0;
}

int main(int argc, char **argv)
{
  int gno;
  if (argc < 2){
    printf("Usage: %s GPIO_NO\n", argv[0]);
    return -1;
  }  
  gno = atoi(argv[1]);

  wiringPiSetup(); // wiringPi 초기화
  ledControl(gno);
}