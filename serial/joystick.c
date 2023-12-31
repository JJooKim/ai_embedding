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
    digitalWrite(CS_MCP3208, 0); // CS Active by making it low
    wiringPiSPIDataRW(SPI_CHANNEL, buff, 3);
    //sending a request to MCP3208 with information of which channel data to send back 



    //You get the data back inside the buffer(need to handle the received data a bit)
    buff[1] = 0x0f & buff[1];
    adcValue = ( buff[1] << 8) | buff[2];
    //buff[1] << 8 shifts the bits in buff[1] 8 positions to the left. This effectively converts buff[1] into the high byte of a 16-bit value, with the four least significant bits being zeros.
    //
    digitalWrite(CS_MCP3208, 1); // High : CS Inactive, finish read data
    return adcValue;
}

int main(void)
{
    int adcValX, adcValY;
    wiringPiSetup();
    wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED);
    pinMode(CS_MCP3208, OUTPUT);
    while(1)
    {
        adcValX = read_mcp3208_adc(0);
        adcValY = read_mcp3208_adc(1);
        printf("X-axis: %u, Y-axis: %u\n", adcValX, adcValY);
        delay(500);
    }
    return 0;
}



