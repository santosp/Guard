/*
 * UiMessages.c
 *
 *  Created on: May 29, 2013
 *      Author: paul
 */

#include "UiMessages.c"

void WelcomeMsg(void){
	draw_text_bmp((INT8U *)"Welcome ",16,40,MyFont,1);
	draw_text_bmp((INT8U *)"Welcome To The Grocery Guard System",16,16,MyFont,1);
	draw_text_bmp((INT8U *)"Please Enter The Current Date in HH:MMPM/AM,MM/DD/YYYY Format",16,24,MyFont,1);
	draw_text_bmp((INT8U *)"Ex) 2:30PM , May 5th 2013",16,32,MyFont,1);
	draw_text_bmp((INT8U *)"02:30PM  05/05/2013 ",16,40,MyFont,1);
}

void WelcomeMsg(void){
	draw_text_bmp((INT8U *)"Welcome ",16,40,MyFont,1);
	draw_text_bmp((INT8U *)"Welcome To The Grocery Guard System",16,16,MyFont,1);
	draw_text_bmp((INT8U *)"Please Enter The Current Date in HH:MMPM/AM,MM/DD/YYYY Format",16,24,MyFont,1);
	draw_text_bmp((INT8U *)"Ex) 2:30PM , May 5th 2013",16,32,MyFont,1);
	draw_text_bmp((INT8U *)"02:30PM  05/05/2013 ",16,40,MyFont,1);
}
