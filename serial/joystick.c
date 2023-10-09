#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <wiringPiSPI.h>
#define CS_MCP3208 10 // BCM_GPIO 8 ,24pin
#define SPI_CHANNEL 0 // one slave SPI
#define SPI_SPEED 1000000 // 1MHz
int read_mcp3208_adc(unsigned char adcChannel)
{
    unsigned char buff[3];
    int adcValue = 0;
    buff[0] = 0x06|((adcChannel & 0x07) >> 2); //d2 on the last bit
    buff[1] = (adcChannel & 0x07) << 6; //d1 and d0 on the first two bits
    buff[2] = 0x00;
    digitalWrite(CS_MCP3208, 0); // Low : CS Active
    wiringPiSPIDataRW(SPI_CHANNEL, buff, 3);
    buff[1] = 0x0f & buff[1];
    adcValue = ( buff[1] << 8) | buff[2];
    digitalWrite(CS_MCP3208, 1); // High : CS Inactive, finish read data
    return adcValue;
}


int main (void)
{
    int adcChannel = 0;
    int adcValue = 0;
    wiringPiSetup();
    pinMode(CS_MCP3208, OUTPUT); //cs output , data input from Dout

    if(wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) == -1)
    {
        printf ( "wiringPiSPISetup Failed: %s\n", strerror(errno));
        return 1;
    }

    for(int i=0;;i++) {
        //adcChannel = i%3;
        adcChannel=1;
        adcValue = read_mcp3208_adc(adcChannel);

        printf("%u", adcValue); //테스트 코드 라인 나오는 값 확인 위해

        switch (adcChannel) {
            case 0 : if (adcValue>800) printf(" X axis turn right %u \n",adcValue);
                else if(adcValue < 200) printf(" X axis turn left %u\n",adcValue);
                else printf(" X no turn %u \n",adcValue);
                break;
            case 1 : if (adcValue>800) printf(" Y backward %u\n",adcValue);
                else if(adcValue < 200) printf(" Y forward %u \n",adcValue);
                else printf(" Y no change %u \n",adcValue);
                break;
            case 2 : if (adcValue>300) printf(" SW OFF %u\n",adcValue);
                else if(adcValue < 50) printf(" SW ON %u \n",adcValue);
                else printf(" SW no change %u \n",adcValue);
                break;
            default : printf(" light Value i=%d = %u\n",adcChannel, adcValue);
            //break;
        }
        //printf("adc0 Value i=%d = %u\n",adcChannel, adcValue);
        delay(500) ; //ms
    }
    return 0;
}
