#include <intrins.h>
#include <REG52.H>    /* special function register declarations   */

#include "Colors.h"
#ifndef LCD9163
	#define LCD9163

	#define LCD_WIDTH 160
	#define LCD_HEIGHT 128

	sbit LCD_CS = P0 ^ 3;
	sbit LCD_RESET = P0 ^ 4;
	sbit LCD_DC = P0 ^ 5;
	sbit LCD_WR = P0 ^ 6;
	sbit LCD_RD = P0 ^ 7;

	void LCD_SendCmd(unsigned int _cmd);
	void LCD_SendData(unsigned int _data);
	unsigned int LCD_readData(void);
	void LCD_Reset(void);
	void LCD_SetColumn(unsigned int x_left, x_right);
	void LCD_SetPage(unsigned int y_up, y_down);
	void LCD_Clear(color _color);
	void LCD_endCom(void);
	void LCD_PrintChar(char _char,int _x,int _y,int _font_height, int _font_width, color _color);
	void LCD_Init(void);
	
#endif

