#include <stdio.h>
#include <stdlib.h> /* atoi( ) 함수*/
#include <string.h>
#include <fcntl.h>
#include <unistd.h> /* close( ) 함수*/

int ledControl(int gpio)
{
  int fd;                 // 파일 디스크립터를 저장할 변수 선언
  char buf[BUFSIZ];       // 문자열을 저장할 버퍼 선언

  fd = open("/sys/class/gpio/export", O_WRONLY); /* 해당 GPIO 디바이스 사용 준비 */
  // "/sys/class/gpio/export" 파일을 쓰기 전용(O_WRONLY)으로 열어서 GPIO 장치를 준비하는 부분

  sprintf(buf, "%d", gpio);  // 문자열 형태로 GPIO 핀 번호를 버퍼에 저장
  write(fd, buf, strlen(buf)); // 저장된 GPIO 핀 번호를 파일에 쓰기
  close(fd);                // 파일 디스크립터 닫기

  sprintf(buf, "/sys/class/gpio/gpio%d/direction", gpio); /* 해당 GPIO 디바이스의 방향 설정*/
  fd = open(buf, O_WRONLY);
  /* LED를 위해 디바이스를 출력으로 설정: 입력의 경우 write(fd, "in", 3); 사용*/
  write(fd, "out", 4);
  close(fd);

  sprintf(buf, "/sys/class/gpio/gpio%d/value", gpio); /* 디바이스에 값 출력 */
  fd = open(buf, O_WRONLY);
  write(fd, "1", 2);
  close(fd);

  getchar(); /* LED 확인을 위한 대기 */
  fd = open("/sys/class/gpio/unexport", O_WRONLY); /* 사용한 GPIO 디바이스 해제하기 */
  sprintf(buf, "%d", gpio);
  write(fd, buf, strlen(buf));
  close(fd);

  return 0;
}


int main(int argc, char **argv)
{
  int gno; // 정수형 변수 gno 선언

  if (argc < 2) { // 프로그램 실행 시 전달된 명령행 인수의 개수가 2 미만인 경우
    printf("Usage: %s GPIO_NO\n", argv[0]); // 사용법 안내 메시지 출력
    return -1; // 프로그램 종료 및 오류 코드(-1) 반환
  }

  gno = atoi(argv[1]); // 명령행 인수로 전달된 문자열을 정수로 변환하여 변수 gno에 저장
  ledControl(gno); // ledControl 함수를 호출하여 GPIO 핀을 제어

  return 0; // 프로그램 정상 종료
}
