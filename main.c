#include <REG52.H>                /* special function register declarations   */
#include <stdio.h>                /* prototype declarations for I/O functions */
#include <string.h>
#include <ctype.h>
#include <intrins.h>

#include "ILI9163_lib.h"
#include "Delay_lib.h"
#include "Colors.h"


int sel = 9,
		print = 0,
		offset = 0;
unsigned int 	i = 0, 
							j = 0,
							k = 0;
unsigned long msec = 0,
							sec = 0;
unsigned int count = 15;		/* 15,25 times is correct */
color col;


void T0Isr(void) interrupt 1 using 1 {
	TF0 = 0;
			count --;
			if (count == 0) {
				count = 100;
				sec ++;
			}
			TH0 = 0xFC;
			TL0 = 0x17;
}
/*
void putc (unsigned char s1){
	SBUF = s1;
	while (!TI);
	TI=0;
}


void UARTInt (void) interrupt 4{
	if (RI) {
		RI = 0;
		print = 1;
	}		
}

void ReadNByte(unsigned int _cmd, unsigned int _n){
	printf("command : %x\n", _cmd);
	LCD_sendCmd(_cmd & 0xFF, 1);
	for (i = 0; i < (_n-1); i++){
		LCD_data = LCD_readData(1);
		printf("%x\n", LCD_data);
	}
	LCD_data = LCD_readData(0);
	printf("%x\n", LCD_data);
	printf("command end\n");
}
*/

void main (void) {
	
//  SCON  = 0x50;		        	/* SCON: mode 1, 8-bit UART, enable rcvr      */
  TMOD |= 0x21;               /* TMOD: timer 1, mode 2, 8-bit reload , timer 0 ...       */
//  TH1   = 230;                /* TH1:  reload value for 1200 baud @ 16MHz  (221) */
//  TR1   = 1;                  /* TR1:  timer 1 run                          */
//  TI    = 1;                  /* TI:   set TI to send first char of UART    */
//	RI 		= 0;
//	IE		=  0x90;
	TH0 = 0;
	TL0 = 0;
	TR0 = 1;									/*start TIMER0*/
	
	
	IE = 0x81;					//enable interrupt timer 0*/
	
	LCD_Init();
//--------------------------	
/*	col.red = 0x00;
	col.green = 0x00;
	col.blue = 0xFF;*/
	col = RED;
	
	while(1){
/*		for (j = 0; j < 5; j++){
			for (i = 0; i < 7; i++){
				if (i+j*7 > 25) goto M1;
				LCD_PrintChar(('A' + i + j*7), i*16, j*16, 16, 16, col);												//TODO: auto detect size of font!!!!!!!
			}
		}
M1:	
		col.green = col.blue;
		col.blue = 0x00;
		for (i = 0; i < 10; i++){
				LCD_PrintChar(('0' + i), i*16, 100, 16, 16, col);			//TODO: auto detect size of font!!!!!!!
			}
		col = BLUE;
		
		LCD_Clear(col);
		*/
		LCD_PrintChar(sec + 33, 16, 16, 16, 16, RED);
		
	}
//--------------------
	
}
