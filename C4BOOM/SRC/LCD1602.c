#include "LCD1602.h"

// 定义全局变量
sbit LCD1602_RW = P2 ^ 5;
sbit LCD1602_RS = P2 ^ 6;
sbit LCD1602_EN = P2 ^ 7;
#define LCD1602_DataPort P0

//声明函数
void LCD1602_Command(unsigned char Command);
void LCD1602_Data(unsigned char Data);
void LCD1602_SetSeat(unsigned char Line, unsigned char Column);
void LCD1602_Init();
void LCD1602_DisplayStr(unsigned char Line, unsigned char Column, char *String);
int LCD1602_Pow(int X, int Y);
void LCD1602_DisplayNum(unsigned char Line, unsigned char Column, int Num, unsigned char Length);
void Delay();

// LCD16021602读入[控制]
// 输入：[command]控制令
// 输出：无
void LCD1602_Command(unsigned char Command)
{
	LCD1602_RW = 0; // 模式[0],[读入]内容
	LCD1602_RS = 0; // 模式[0],内容[控制]
	LCD1602_DataPort = Command;
	LCD1602_EN = 1; // 使能，开始读入
	Delay();
	LCD1602_EN = 0; // 不使能，停止读入
	Delay();
}
// LCD16021602读入[数据]
// 输入：[Data]数据
// 输出：无
void LCD1602_Data(unsigned char Data)
{
	LCD1602_RW = 0; // 模式[0]，[读入]内容
	LCD1602_RS = 1; // 模式[1],内容[数据]
	LCD1602_DataPort = Data;
	LCD1602_EN = 1; // 使能，开始读入
	Delay();
	LCD1602_EN = 0; // 不使能，停止读入
	Delay();
}
// 初始化LCD16021602
// 输入：无
// 输出：无
void LCD1602_Init()
{

	LCD1602_Command(0x38); // 八位数据接口，两行显示，5*7点阵
	LCD1602_Command(0x0c); // 显示开，光标关，闪烁关
	LCD1602_Command(0x06); // 数据读写操作后，光标自动加一，画面不动
	LCD1602_Command(0x01); // 光标复位，清屏
}
// 控制光标位置
// 输入：行列
// 输出：控制令[LCD1602_Command]→设置→光标
void LCD1602_SetSeat(unsigned char Line, unsigned char Column)
{
	if (Line == 1) //[1]行
	{
		LCD1602_Command(0x80 | (Column - 1)); //[Column]列
	}
	else if (Line == 2) //[2]行
	{
		LCD1602_Command(0x80 | (Column - 1 + 0x40)); //[Column]列
	}
}
// 读入字符串
// 输入：显示位置：[行] [列] 显示内容：[字符串]
// 输出：显示数据[LCD1602_Data] →LCD16021602显示→ LCD16021602屏幕
void LCD1602_DisplayStr(unsigned char Line, unsigned char Column, char *String)
{
	unsigned char i;
	LCD1602_SetSeat(Line, Column);
	for (i = 0; String[i] != '\0'; i++)
	{
		LCD1602_Data(String[i]);
	}
}
// 整形取出[取平方]
int LCD1602_Pow(int X, int Y)
{
	unsigned char i;
	int Result = 1;
	for (i = 0; i < Y; i++)
	{
		Result *= X;
	}
	return Result;
}
// 显示整形数
// 输入：显示位置：[行] [列] 显示内容：[整形数] [长度]
// 输出：显示数据[LCD1602_Data] →LCD16021602显示→ LCD16021602屏幕
void LCD1602_DisplayNum(unsigned char Line, unsigned char Column, int Num, unsigned char Length)
{
	
	unsigned char i;
	unsigned int Num1;
	LCD1602_SetSeat(Line, Column);
	if (Num >= 0)
	{
		Num1 = Num;
	}
	else
	{
		LCD1602_Data('-');
		Num1 = -Num;
	}
	for (i = Length; i > 0; i--)
	{
		LCD1602_Data(Num1 / LCD1602_Pow(10, i - 1) % 10 + '0');
	}
}
void LCD1602_Clean(uChar Line)
{
	uChar i;
	switch (Line)
	{
	case 1:
		LCD1602_Command(0x80);
		for (i = 0; i < 16; i++)
		{
			LCD1602_Data(0x20);
		}
		break;
	case 2:
		LCD1602_Command(0x80+0x40);
		for (i = 0; i < 16; i++)
		{
			LCD1602_Data(0x20);
		}
	case 0:
		LCD1602_Command(0x01);
	default:
		break;
	}
	
}
// 延迟
void Delay()
{
	unsigned char a, b, c;
	for (c = 1; c > 0; c--)
		for (b = 142; b > 0; b--)
			for (a = 2; a > 0; a--);
}
