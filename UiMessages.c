/*
 * UiMessages.c
 *
 *  Created on: May 29, 2013
 *      Author: paul
 */

#include "UiMessages.h"

void WelcomeMsg(void){
	draw_text_bmp((INT8U *)"Welcome ",44,TPAGE0,MyFont,1);
	draw_text_bmp((INT8U *)"To The Grocery Guard System",12,TPAGE1,MyFont,1);
	draw_text_bmp((INT8U *)"Please Enter The Date in ",12,TPAGE2,MyFont,1);
	draw_text_bmp((INT8U *)"HH:MMPM,MM/DD/YY Format",8,TPAGE3,MyFont,1);
	draw_text_bmp((INT8U *)"Ex) 2:30PM , May 5th 2013",8,TPAGE4,MyFont,1);
	draw_text_bmp((INT8U *)"02:30PM  05/05/2013 ",16,TPAGE5,MyFont,1);
	//inverted box on page 6
}

void WelcomeMsg2(void){
	glcd_blank_page(LPAGE0);
	glcd_blank_page(LPAGE1);
	glcd_blank_page(LPAGE2);
	glcd_blank_page(LPAGE3);
	glcd_blank_page(LPAGE4);
	draw_text_bmp((INT8U *)"Wrong Format/Invalid Input",16,TPAGE0,MyFont,1);
	draw_text_bmp((INT8U *)"Please try again",16,TPAGE1,MyFont,1);
	draw_text_bmp((INT8U *)"Please Enter The Current Date in HH:MMPM/AM,MM/DD/YYYY Format",16,TPAGE2,MyFont,1);
	draw_text_bmp((INT8U *)"Ex) 2:30PM , May 5th 2013",16,TPAGE3,MyFont,1);
	draw_text_bmp((INT8U *)"02:30PM  05/05/2013 ",16,TPAGE4,MyFont,1);
	//inverted box on page 6
}

void MainMsg(void){
	glcd_blank_page(LPAGE0);
	glcd_blank_page(LPAGE1);
	glcd_blank_page(LPAGE2);
	glcd_blank_page(LPAGE3);
	glcd_blank_page(LPAGE4);
	glcd_blank_page(LPAGE5);
	glcd_blank_page(LPAGE6);
	draw_line(1,8,128,8,1);
	draw_line(33,1,33,8,1);
	draw_line(96,1,96,8,1);
	glcd_blank_pagexy(LPAGE1,34,95);
	draw_text_bmp((INT8U *)"Main Menu",44,TPAGE0,MyFont,1);
	draw_text_bmp((INT8U *)"Please Select an Option",16,TPAGE2,MyFont,1);
	draw_text_bmp((INT8U *)"Using the Buttons Below",16,TPAGE3,MyFont,1);
	draw_line(1,PAGE6,128,PAGE6,1);
	draw_line(31,49,31,64,1);
	draw_line(63,49,63,64,1);
	draw_line(95,49,95,64,1);
	//last two pages with F1=~Blank, F2= Remove Item, F3 = Add Item, F4 = View Inv
}

void AddMsg(void){
	glcd_blank_pagexy(LPAGE1,34,95);
	glcd_blank_page(LPAGE1);
	glcd_blank_page(LPAGE2);
	glcd_blank_page(LPAGE3);
	glcd_blank_page(LPAGE4);
	glcd_blank_page(LPAGE5);
	draw_text_bmp((INT8U *)"Add Item",44,TPAGE0,MyFont,1);
	draw_text_bmp((INT8U *)"Please use Barcodescanner Or Keyboard",16,TPAGE2,MyFont,1);
	draw_text_bmp((INT8U *)"to enter UPC",16,TPAGE3,MyFont,1);
	//inverted box on page 4
	//last two pages with F1=Main Menu, F2=Remove Item, F3=Add By Name, F4=View Inv
}

void AddMsgInvalid(void){
	draw_text_bmp((INT8U *)"Add Item",44,TPAGE0,MyFont,1);
	draw_text_bmp((INT8U *)"Invalid Format",16,TPAGE2,MyFont,1);
	draw_text_bmp((INT8U *)"Please enter only numbers",16,TPAGE3,MyFont,1);
	//inverted box on page 4
}

void AddMsgFound(void){
	draw_text_bmp((INT8U *)"Add Item",44,TPAGE0,MyFont,1);
	draw_text_bmp((INT8U *)"Found!",16,TPAGE2,MyFont,1);
	//insert item name after fount on page2
	draw_text_bmp((INT8U *)"Please Enter Expiration Date",1,TPAGE3,MyFont,1);
	draw_text_bmp((INT8U *)"In Format MM/DD/YYYY",1,TPAGE4,MyFont,1);
	//inverted box on page 5
}

void AddMsgFoundWrongF(void){
	draw_text_bmp((INT8U *)"Add Item",44,TPAGE0,MyFont,1);
	draw_text_bmp((INT8U *)"Wrong Format",16,TPAGE2,MyFont,1);
	draw_text_bmp((INT8U *)"Please Enter Expiration Date in MMDDYYYY",1,TPAGE3,MyFont,1);
	//inverted box on page 5

}

void AddMsgNoMatch(void){
	draw_text_bmp((INT8U *)"Add Item",44,TPAGE0,MyFont,1);
	draw_text_bmp((INT8U *)"No UPC Match in Database",16,TPAGE1,MyFont,1);
	draw_text_bmp((INT8U *)"Would you like to ",1,TPAGE2,MyFont,1);
	draw_text_bmp((INT8U *)"Add UPC to database?",1,TPAGE3,MyFont,1);
	draw_text_bmp((INT8U *)"Try Again?",1,TPAGE4,MyFont,1);
	draw_text_bmp((INT8U *)"Or Go Back To Main Menu?",1,TPAGE5,MyFont,1);
	//last two pages with F1=Main Menu, F2= ~blank, F3 = Add to database, F4 = Try again
}

void AddMsgNewExp(void){
	draw_text_bmp((INT8U *)"Add Item",44,TPAGE0,MyFont,1);
	draw_text_bmp((INT8U *)"Please Enter Expiration Date",16,TPAGE1,MyFont,1);
	draw_text_bmp((INT8U *)"In Format MM/DD/YYYY",1,TPAGE2,MyFont,1);

	//last two pages with F1=Main Menu, F2= ~blank, F3 = Add to database, F4 = Try again
}
