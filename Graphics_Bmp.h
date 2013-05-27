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


extern bounding_box_t draw_text_bmp(INT8U *string, unsigned char x, unsigned char y, const unsigned char *font, unsigned char spacing);

bounding_box_t draw_char_bmp(unsigned char c, unsigned char x, unsigned char y,const unsigned char *font) ;

extern void GlcdDispTime(INT8U hrs, INT8U min, INT8U sec);

#endif /* GRAPHICS_BMP_H_ */
