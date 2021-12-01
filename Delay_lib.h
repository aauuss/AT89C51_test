#ifndef DELAY_LIB
	#define DELAY_LIB

	#ifndef F_CPU
		#define F_CPU 12000000
	#endif

	void delay(unsigned long _time);

#endif