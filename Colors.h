#ifndef COLORS
	#define COLORS

	typedef struct {
		int red,
				green,
				blue;
	} color;


	static color RED = {0xFF, 0x00, 0x00};
	static color GREEN = {0x00, 0xFF, 0x00};
	static color BLUE = {0x00, 0x00, 0xFF};
	static color BLACK = {0x00, 0x00, 0x00};
	static color WHITE = {0xFF, 0xFF, 0xFF};

#endif
