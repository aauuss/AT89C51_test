#include "ILI9163_lib.h"
#include <ctype.h>
#include <intrins.h>
#include "Font16x16.h"
#include "Colors.h"

#include "Delay_lib.h"

unsigned int counter, _i, _j, _k;

void LCD_endCom(void){
	LCD_CS = 1;
}

void LCD_SendCmd(unsigned int _cmd){
	LCD_CS = 0;
	LCD_DC = 0;
//	delay(2);
	LCD_RD = 1;	
	LCD_WR = 0;
	P2 = _cmd & 0xFF;			//??	
//	delay(6);
	LCD_WR = 1;
//	delay(6);
//	if (_cont == 0){
//		LCD_CS = 1;
//	}
	P2 = 0xFF;
}

void LCD_SendData(unsigned int _data){
	LCD_CS = 0;
	LCD_DC = 1;
//	delay(2);
	LCD_RD = 1;
	LCD_WR = 0;
	P2 = _data & 0xFF;
//	delay(6);
	LCD_WR = 1;
//	delay(6);
//	if (_cont == 0) {
//		LCD_CS = 1;
//	}
//	P2 = 0xFF;
}

unsigned int LCD_readData(void){
	unsigned int _data;
	P2 = 0xff;
	LCD_DC = 1;
//	delay(2);
	LCD_CS = 0;
//	delay(2);
	LCD_WR = 1;
	LCD_RD = 0;
//	delay(5);
	LCD_RD = 1;
	_data = P2 & 0xFF;
	
//	if (_cont == 0) {
//		LCD_CS = 1;
//	}
	return _data;	
}

void LCD_Init(void){
	P2 = 0xFF;
	delay(10);

	LCD_Reset();
	delay(1000);
	
	LCD_SendCmd(0x01);
	LCD_endCom();
	delay(1000);

  LCD_SendCmd(0x11);
	LCD_endCom();
	delay(100);
		
	LCD_SendCmd(0x13);
	LCD_endCom();
	delay(100);
			
	LCD_SendCmd(0x3A);
	LCD_SendData(0x66);
	delay(10);
			
	LCD_SetColumn(0x00,0x7F);
	delay(10);
	LCD_SetPage(0x00,0x9F);
	delay(10);
			
	LCD_SendCmd(0x36);
	LCD_SendData(0xBC);
	LCD_endCom();
			
	LCD_SendCmd(0x29);	
	LCD_endCom();
	
	LCD_SendCmd(0xB1);
	LCD_SendData(0x03);
	LCD_SendData(0x01);
	LCD_endCom();
}

void LCD_SetColumn(unsigned int x_left, x_right){
	LCD_SendCmd(0x2A);
	LCD_SendData(0x00);//x_left >> 8, 1);
	LCD_SendData(x_left & 0xFF);
	LCD_SendData(0x00);//x_right >> 8, 1);
	LCD_SendData(x_right & 0xFF);	
	LCD_endCom();
}

void LCD_SetPage(unsigned int y_up, y_down){
	LCD_SendCmd(0x2B);
	LCD_SendData(0x00);//(y_up >> 8), 1);
	LCD_SendData((y_up & 0xFF));
	LCD_SendData(0x00);//(y_down >> 8), 1);
	LCD_SendData((y_down & 0xFF));
	LCD_endCom();
}

void LCD_Reset(void) {
	LCD_RESET = 0;
	LCD_RESET = 1;
}

void LCD_Clear(color _color){
	LCD_SetColumn(0, LCD_WIDTH);
	LCD_SetPage(0, LCD_HEIGHT);
	LCD_SendCmd(0x2C);
	for (counter = 0; counter < LCD_WIDTH * LCD_WIDTH - 1; counter++){
		LCD_SendData(_color.red);
		LCD_SendData(_color.green);
		LCD_SendData(_color.blue);
	}
}

void LCD_PrintChar(char _char,int _x,int _y,int _font_height, int _font_width, color _color){	
	LCD_SetPage(_y, _y + _font_height - 1);
	LCD_SetColumn(_x, _x + _font_width - 1);
	LCD_SendCmd(0x2C);
	for (_j = 0; _j < (_font_height * _font_width >> 3) ; _j++){
		for (_k = 0; _k < 8; _k++){
			if (Font16x16[_char - 32][_j] & (1 << (7 -_k))){
				LCD_SendData(_color.red);
				LCD_SendData(_color.green);
				LCD_SendData(_color.blue);
			} else {
				LCD_SendData(0x00);
				LCD_SendData(0x00);
				LCD_SendData(0x00);			
			}
		}
	}
	LCD_endCom();

}