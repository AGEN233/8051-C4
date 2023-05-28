#include "MatirxKey.h"
void MatirxKey_Delay(void);
#define MatirxKey_PORT P1
uChar MatirxKey_Number = 0;
uChar MatirxKey(void)
{
    MatirxKey_PORT = 0x0f;      // P1.0-1.3输出高电平，P1.4-P1.7输出低电平
    if (MatirxKey_PORT != 0x0f) // 读取MatirxKey_PORT看是否有按键按下
    {
        MatirxKey_Delay();                    // 延时消抖
        if (MatirxKey_PORT != 0x0f) // 确认确实有按键按下
        {
            // 先确定按键发生在第几列
            switch (MatirxKey_PORT)
            {
            case 0x07:
                MatirxKey_Number = 1;
                break;
            case 0x0b:
                MatirxKey_Number = 2;
                break;
            case 0x0d:
                MatirxKey_Number = 3;
                break;
            case 0x0e:
                MatirxKey_Number = 4;
                break;
            default:
                break;
            }
            // 再确定按键发生在第几行
            MatirxKey_PORT = 0xf0;
            switch (MatirxKey_PORT)
            {
            case 0x70:
                MatirxKey_Number = MatirxKey_Number + 0;
                break;
            case 0xb0:
                MatirxKey_Number = MatirxKey_Number + 4;
                break;
            case 0xd0:
                MatirxKey_Number = MatirxKey_Number + 8;
                break;
            case 0xe0:
                MatirxKey_Number = MatirxKey_Number + 12;
                break;
            }
            while (MatirxKey_PORT != 0xf0);
        }
        return MatirxKey_Number;
    }
    return 0;
}
void MatirxKey_Delay(void)
{
    uChar a, b,c;
    for (c = 1; c > 0; c--)
        for (b = 38; b > 0; b--)
            for (a = 130; a > 0; a--)
                ;
}
