#include <intrins.h>
#include "Delay_lib.h"

void delay(unsigned long _time){
//	_time = _time * 20;
	while (_time != 0) {
		_time--;
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();		
	}
}