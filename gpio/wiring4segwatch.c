#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Include the time.h header for time functions

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

// Wpi pin numbers
char pins[8] = {PA, PB, PC, PD, PE, PF, PG, PDEC};
char pindps[4] = {PDP1, PDP2, PDP3, PDP4};

void clear_pin()
{
    int i;
    for (i = 0; i < 8; i++)
        digitalWrite(pins[i], 1);
    for (i = 0; i < 4; i++)
        digitalWrite(pindps[i], 1);
}

void set_pin(int n)
{
    int i;
    for (i = 0; i < 8; i++)
        digitalWrite(pins[i], (n >> i) & 0x1);
}

void init_pin()
{
    int i;
    for (i = 0; i < 8; i++)
        pinMode(pins[i], OUTPUT);
    for (i = 0; i < 4; i++)
        pinMode(pindps[i], OUTPUT);
}

int main(void)
{
    wiringPiSetup();
    init_pin();

    //clear_pin();

    time_t curr_time;
    time(&curr_time);


    struct tm *timeInfo;

    timeInfo = localtime(&curr_time); // Convert to local time

    int hours = timeInfo->tm_hour;
    int minutes = timeInfo->tm_min;

    // Display the hours and minutes
    
    clear_pin();
    digitalWrite(PDP2, 0);    // Enable the first digit (leftmost)
    digitalWrite(PDP3, 0);
    digitalWrite(PDP4, 0);
    set_pin(hours / 10);       // Display tens digit of hours
    delay(1000);                  // Delay to display the digit
    
    clear_pin();
    digitalWrite(PDP1, 0);    // Enable the first digit (leftmost)
    digitalWrite(PDP3, 0);
    digitalWrite(PDP4, 0);
    set_pin(hours % 10);       // Display tens digit of hours
    delay(1000);                  // Delay to display the digit


    clear_pin();
    digitalWrite(PDP1, 0);    // Enable the first digit (leftmost)
    digitalWrite(PDP2, 0);
    digitalWrite(PDP4, 0);
    set_pin(minutes / 10);       // Display tens digit of hours
    delay(1000);                  // Delay to display the digit


    clear_pin();
    digitalWrite(PDP1, 0);    // Enable the first digit (leftmost)
    digitalWrite(PDP2, 0);
    digitalWrite(PDP3, 0);
    set_pin(minutes / 10);       // Display tens digit of hours
    delay(1000);                  // Delay to display the digit

    delay(1000); // Delay for one second


    // while (1) // 무한 루프
    // {
    //     time_t curr_time;
    //     time(&curr_time)


    //     struct tm *timeInfo;

    //     timeInfo = localtime(&curr_time); // Convert to local time

    //     int hours = timeInfo->tm_hour;
    //     int minutes = timeInfo->tm_min;

    //     // Display the hours and minutes
    //     set_pin(hours / 10);       // Display tens digit of hours
    //     digitalWrite(PDP1, 1);    // Enable the first digit (leftmost)
    //     delay(5);                  // Delay to display the digit
    //     digitalWrite(PDP1, 0);    // Disable the first digit

    //     set_pin(hours % 10);       // Display ones digit of hours
    //     digitalWrite(PDP2, 1);    // Enable the second digit
    //     delay(5);                  // Delay to display the digit
    //     digitalWrite(PDP2, 0);    // Disable the second digit

    //     set_pin(minutes / 10);     // Display tens digit of minutes
    //     digitalWrite(PDP3, 1);    // Enable the third digit
    //     delay(5);                  // Delay to display the digit
    //     digitalWrite(PDP3, 0);    // Disable the third digit

    //     set_pin(minutes % 10);     // Display ones digit of minutes
    //     digitalWrite(PDP4, 1);    // Enable the fourth digit (rightmost)
    //     delay(5);                  // Delay to display the digit
    //     digitalWrite(PDP4, 0);    // Disable the fourth digit

    //     delay(1000); // Delay for one second
    // }

    return 0;
}
