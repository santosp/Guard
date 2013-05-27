/*
 * graphics_bmp.c
 *
 *  Created on: Apr 19, 2013
 *      Author: AGV-EET
 */
#include "Graphics_Bmp.h"

INT8U time_string[10];

bounding_box_t draw_text_bmp(INT8U *string, unsigned char x, unsigned char y, const unsigned char *font, unsigned char spacing) {
	bounding_box_t ret;
	bounding_box_t tmp;
	INT8U j = 0;
	ret.x1 = x;
	ret.y1 = y;

	spacing += 1;

	// BUG: As we move right between chars we don't actually wipe the space
	while (*string != 0) {
		tmp = draw_char_bmp(*string++, x, y, font);

		// Leave a single space between characters

		if(spacing>0){
			for ( j = 0; j < 6; j++) {
					glcd_pixel(tmp.x2+1, tmp.y1+j, 0);
			}
			x = tmp.x2 + spacing;
		}

	}

	ret.x2 = tmp.x2;
	ret.y2 = tmp.y2;

	return ret;
}

bounding_box_t draw_char_bmp(unsigned char c, unsigned char x, unsigned char y,const unsigned char *font) {
	unsigned int pos=0;
	unsigned char width;
	bounding_box_t ret;

	ret.x1 = x;
	ret.y1 = y;
	ret.x2 = x;
	ret.y2 = y;


	// Work out where in the array the character is
	pos = (256*font[(c - 29)+(c-32)])+(font[(c - 29)+(c-31)]);


	// Read first byte from this position, this gives letter width
	width = font[pos];

	// Draw left to right
	unsigned char i;
	unsigned char j;
	for (i = 0; i < width; i++) {

		// Draw top to bottom
		for ( j = 0; j < font[BMP_HEIGHT]; j++) {
			// Increment one data byte every 8 bits, or
			// at the start of a new column  HiTech optimizes
			// the modulo, so no need to try and avoid it.
			if (j % 8 == 0) pos++;

			if (font[pos] & 1 << (j % 8)) {
				glcd_pixel(x + i, y + j, 1);
			} else {
				glcd_pixel(x + i, y + j, 0);
			}
		}
	}

	ret.x2 = ret.x1 + width - 1;
	// TODO: Return the actual height drawn, rather than the height of the
	//		 font.
	//ret.y2 = ret.y1 + height;
	ret.y2 = ret.y1 + font[FONT_HEADER_HEIGHT];

	return ret;
}

void GlcdDispTime(INT8U hrs, INT8U min, INT8U sec){
	INT8U tens, ones;

	ones = (hrs % 10) +'0';
	hrs = hrs/10;
	tens = (hrs % 10) +'0';

	time_string[0]=tens;
	time_string[1]=ones;
	time_string[2]=':';

	ones = (min % 10) +'0';
	min = min/10;
	tens = (min % 10) +'0';

	time_string[3]=tens;
	time_string[4]=ones;
	time_string[5]=':';

	ones = (sec % 10) +'0';
	sec = sec/10;
	tens = (sec % 10) +'0';

	time_string[6]=tens;
	time_string[7]=ones;

	draw_text_bmp(time_string,1,1,MyFont,1);
}
