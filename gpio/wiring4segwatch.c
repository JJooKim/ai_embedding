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

void clear_pin()
{
    int i;
    for (i = 0; i < 8; i++)
        digitalWrite(pins[i], 1);
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
}

int main(void)
{
    wiringPiSetup();
    init_pin();

    while (1) // Run continuously
    {
        time_t rawTime;
        struct tm *timeInfo;

        time(&rawTime);          // Get current time
        timeInfo = localtime(&rawTime); // Convert to local time

        int hours = timeInfo->tm_hour;
        int minutes = timeInfo->tm_min;

        // Display the hours and minutes
        set_pin(hours / 10);       // Display tens digit of hours
        digitalWrite(PDP1, 0);    // Enable the first digit (leftmost)
        delay(5);                  // Delay to display the digit
        digitalWrite(PDP1, 1);    // Disable the first digit

        set_pin(hours % 10);       // Display ones digit of hours
        digitalWrite(PDP2, 0);    // Enable the second digit
        delay(5);                  // Delay to display the digit
        digitalWrite(PDP2, 1);    // Disable the second digit

        set_pin(minutes / 10);     // Display tens digit of minutes
        digitalWrite(PDP3, 0);    // Enable the third digit
        delay(5);                  // Delay to display the digit
        digitalWrite(PDP3, 1);    // Disable the third digit

        set_pin(minutes % 10);     // Display ones digit of minutes
        digitalWrite(PDP4, 0);    // Enable the fourth digit (rightmost)
        delay(5);                  // Delay to display the digit
        digitalWrite(PDP4, 1);    // Disable the fourth digit

        delay(1000); // Delay for one second
    }

    return 0;
}
