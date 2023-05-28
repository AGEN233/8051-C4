#include "public.h"
#include "BUZZ.h"
#include "MatirxKey.h"
#include "LCD1602.h"
#include "delay.h"
#include "string.h"
#define LED P2
uChar password[7] = {10, 10, 10, 10, 10, 10, 10};
code uChar passwordSave[] = {7, 3, 5, 5, 6, 0, 8};
uChar count;
void startBomm(void)
{
    uInit i;
    LCD1602_Clean(0);
    for (i = 0; i < 60; i++)
    {
        LED = 0x00;
        LCD1602_DisplayStr(1, 2, "Now Start BOOM");
        Buzzer_Time(100);
        LED = 0xff;
        LCD1602_Clean(1);
        delay(1000 - (16 * i));
    }

    for (i = 0; i < 25; i++)
    {
        LED = 0x00;
        LCD1602_DisplayStr(2, 1, "000000");
        Buzzer_Time(100);
        LED = 0xff;
        LCD1602_Clean(1);
        delay(24 - i);
    }
    LCD1602_Clean(0);
    LCD1602_DisplayStr(2, 1, "******");
    for (i = 0; i < 5; i++)
    {
        P2 = 0x00;
        Buzzer_Time(50);
        P2 = 0xFF;
    }
    while (1)
        ;
}
void passworldError(void)
{
    while (1)
    {
        LCD1602_Clean(2);
        Buzzer_Time(100);
        LCD1602_DisplayStr(2, 1, "PassWorld ERROR");
        delay(10000);
        LCD1602_DisplayStr(2, 2, "Please  Reboot");
        delay(10000);
    }
}
void DisplayNum(void)
{
    uChar i;
    for (i = 0; i < count; i++)
    {
        LCD1602_DisplayNum(2, (4 + (8 - count) + i), password[i], 1);
        LCD1602_DisplayStr(2, 1, "PWD:");
    }
}
void C4(void)
{
    uChar KeyNum = 0;
    uChar i = 0;
    LCD1602_Init();
    LCD1602_DisplayStr(1, 3, "This C4 Boom");
    LCD1602_DisplayStr(2, 1, "PWD:*******");
    count = 0;
    while (1)
    {
        uChar i = 0;
        KeyNum = MatirxKey();
        if (KeyNum)
        {
            if (KeyNum <= 10)
            {
                password[count++] = KeyNum;
                DisplayNum();
            }
            if (KeyNum == 11)
            {
                for (i = 0; i < 7; i++)
                {
                    if (password[i] == passwordSave[i])
                    {
                        LCD1602_Clean(1);
                        startBomm();
                    }
                    else
                    {
                        passworldError();
                    }
                }
            }
        }
    }
}
void main(void)
{
    C4();
}