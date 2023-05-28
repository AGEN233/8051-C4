#ifndef __LCD1602_H__
#define __LCD1602_H__
#include "public.h"
void LCD1602_Init();
void LCD1602_DisplayStr(unsigned char Line, unsigned char Column, char *String);
void LCD1602_DisplayNum(unsigned char Line, unsigned char Column, int Num, unsigned char Length);
void LCD1602_Clean(uChar Line);
#endif