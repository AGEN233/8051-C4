#include "BUZZ.h"
#include "delay.h"
sbit Buzzer = P2 ^ 5;
void Buzzer_Time(uInit ms)
{

    uInit i;

    for (i = 0; i < ms; i++)
    {

        Buzzer = !Buzzer;
        delay(1);
    }
}