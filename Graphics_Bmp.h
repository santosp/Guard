/*
 * Graphics_Bmp.h
 *
 *  Created on: Apr 19, 2013
 *      Author: AGV-EET
 */

#ifndef GRAPHICS_BMP_H_
#define GRAPHICS_BMP_H_

#include "graphics.h"
#include <stdlib.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "Code_Standards.h"
#include "st7565.h"
#include "Font.h"

#define PAGE0 1
#define PAGE1 9
#define PAGE2 17
#define PAGE3 25
#define PAGE4 33
#define PAGE5 41
#define PAGE6 49
#define PAGE7 57

#define TPAGE0 2
#define TPAGE1 10
#define TPAGE2 18
#define TPAGE3 26
#define TPAGE4 34
#define TPAGE5 42
#define TPAGE6 50
#define TPAGE7 58

#define LPAGE0 1
#define LPAGE1 2
#define LPAGE2 3
#define LPAGE3 4
#define LPAGE4 5
#define LPAGE5 6
#define LPAGE6 7
#define LPAGE7 8

extern bounding_box_t draw_text_bmp(INT8U *string, unsigned char x, unsigned char y, const unsigned char *font, unsigned char spacing);

bounding_box_t draw_char_bmp(unsigned char c, unsigned char x, unsigned char y,const unsigned char *font) ;

extern void GlcdDispTime(INT8U hrs, INT8U min, INT8U sec); //Source Todd Morton, Implemented by Paul Santos

#endif /* GRAPHICS_BMP_H_ */
