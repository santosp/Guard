/*
 * UiMessages.c
 *
 *  Created on: May 29, 2013
 *      Author: paul
 */

#include "UiMessages.h"
#include "Ps2Keyboard.h"
extern INT8U ItemLookUp[][2];
extern ITEMINFO ItemBlock1[25];

void WelcomeMsg(void){
	draw_text_bmp((INT8U *)"Welcome ",44,TPAGE0,MyFont,1);
	draw_text_bmp((INT8U *)"To The Grocery Guard System",12,TPAGE1,MyFont,1);
	draw_text_bmp((INT8U *)"Please Enter The Date in ",12,TPAGE2,MyFont,1);
	draw_text_bmp((INT8U *)"HH:MMPM,MM/DD/YY Format",8,TPAGE3,MyFont,1);
	draw_text_bmp((INT8U *)"Ex) 2:30PM , May 5th 2013",8,TPAGE4,MyFont,1);
	draw_text_bmp((INT8U *)"02:30PM  05/05/2013 ",16,TPAGE5,MyFont,1);
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
	glcd_blank_page(LPAGE7);
	draw_line(1,8,128,8,1);
	draw_line(33,1,33,8,1);
	draw_line(96,1,96,8,1);
	glcd_blank_pagexy(LPAGE1,34,95);
	draw_text_bmp((INT8U *)"Main Menu",44,TPAGE0,MyFont,1);
	draw_text_bmp((INT8U *)"Please Select an Option",16,TPAGE2,MyFont,1);
	draw_text_bmp((INT8U *)"Using the Function Keys",16,TPAGE3,MyFont,1);
	draw_text_bmp((INT8U *)"On Keyboard(F1-F4)",16,TPAGE3,MyFont,1);
	draw_line(1,PAGE6,128,PAGE6,1);
	draw_line(31,49,31,64,1);
	draw_line(63,49,63,64,1);
	draw_line(95,49,95,64,1);
	//F1
	draw_text_bmp((INT8U *)"Main",1,FPAGE6,MyFont,1);
	draw_text_bmp((INT8U *)"Menu",1,FPAGE7,MyFont,1);
	//F2
	draw_text_bmp((INT8U *)"Remove",33,FPAGE6,MyFont,1);
	draw_text_bmp((INT8U *)" Item",33,FPAGE7,MyFont,1);
	//F3
	draw_text_bmp((INT8U *)" Add ",65,FPAGE6,MyFont,1);
	draw_text_bmp((INT8U *)" Item",65,FPAGE7,MyFont,1);
	//F4
	draw_text_bmp((INT8U *)" View ",97,FPAGE6,MyFont,1);
	draw_text_bmp((INT8U *)" Stock",97,FPAGE7,MyFont,1);
	//last two pages with F1=~Blank, F2= Remove Item, F3 = Add Item, F4 = View Inv
}

void AddMsg(void){
	glcd_blank_pagexy(LPAGE1,34,95);
	glcd_blank_page(LPAGE1);
	glcd_blank_page(LPAGE2);
	glcd_blank_page(LPAGE3);
	glcd_blank_page(LPAGE4);
	glcd_blank_page(LPAGE5);
	glcd_blank_page(LPAGE6);
	glcd_blank_page(LPAGE7);
	draw_line(1,8,128,8,1);
	draw_line(33,1,33,8,1);
	draw_line(96,1,96,8,1);
	draw_text_bmp((INT8U *)"Add Item",44,TPAGE0,MyFont,1);
	draw_text_bmp((INT8U *)"Please use Barcodescanner Or",16,TPAGE2,MyFont,1);
	draw_text_bmp((INT8U *)"Keyboard to Enter UPC",16,TPAGE3,MyFont,1);
	draw_line(1,PAGE6,128,PAGE6,1);
	draw_line(31,49,31,64,1);
	draw_line(63,49,63,64,1);
	draw_line(95,49,95,64,1);
	//F1
	draw_text_bmp((INT8U *)"Main",1,FPAGE6,MyFont,1);
	draw_text_bmp((INT8U *)"Menu",1,FPAGE7,MyFont,1);
	//F2
	draw_text_bmp((INT8U *)"Remove",33,FPAGE6,MyFont,1);
	draw_text_bmp((INT8U *)" Item",33,FPAGE7,MyFont,1);
	//F3
	//Might Possibly Add "Add by Item"
	//draw_text_bmp((INT8U *)" Add ",65,FPAGE6,MyFont,1);
	//draw_text_bmp((INT8U *)" Item",65,FPAGE7,MyFont,1);
	//F4
	draw_text_bmp((INT8U *)" View ",97,FPAGE6,MyFont,1);
	draw_text_bmp((INT8U *)" Stock",97,FPAGE7,MyFont,1);draw_text_bmp((INT8U *)"to enter UPC",16,TPAGE3,MyFont,1);

	//inverted box on page 4
	//last two pages with F1=Main Menu, F2=Remove Item, F3=Add By Name, F4=View Inv
}


void AddMsgFound(void){
	glcd_blank_page(LPAGE1);
	glcd_blank_page(LPAGE2);
	glcd_blank_page(LPAGE3);
	glcd_blank_page(LPAGE4);
	glcd_blank_page(LPAGE5);
	glcd_blank_page(LPAGE6);
	glcd_blank_page(LPAGE7);
	draw_line(1,PAGE6,128,PAGE6,1);
	draw_line(31,49,31,64,1);
	draw_line(63,49,63,64,1);
	draw_line(95,49,95,64,1);
	draw_text_bmp((INT8U *)"Found!: ",1,TPAGE1,MyFont,1);
	//insert item name after fount on page2
	draw_text_bmp((INT8U *)"Please Enter Expiration Date",1,TPAGE2,MyFont,1);
	draw_text_bmp((INT8U *)"In Format MM/DD/YYYY",1,TPAGE3,MyFont,1);
	draw_text_bmp((INT8U *)"And then press enter",1,TPAGE4,MyFont,1);
	//inverted box on page 5
}

void AddMsgQuan(void){
	glcd_blank_page(LPAGE1);
	glcd_blank_page(LPAGE2);
	glcd_blank_page(LPAGE3);
	glcd_blank_page(LPAGE4);
	glcd_blank_page(LPAGE5);
	glcd_blank_page(LPAGE6);
	glcd_blank_page(LPAGE7);
	draw_line(1,PAGE6,128,PAGE6,1);
	draw_line(31,49,31,64,1);
	draw_line(63,49,63,64,1);
	draw_line(95,49,95,64,1);
	//insert item name after fount on page2
	draw_text_bmp((INT8U *)"Please Enter Quantity",1,TPAGE1,MyFont,1);
	draw_text_bmp((INT8U *)"In Format 005",1,TPAGE3,MyFont,1);
	draw_text_bmp((INT8U *)"(Max 255)",1,TPAGE4,MyFont,1);
	//inverted box on page 5
}
void AddMsgNoMatch(void){

	glcd_blank_pagexy(LPAGE1,34,95);
	glcd_blank_page(LPAGE1);
	glcd_blank_page(LPAGE2);
	glcd_blank_page(LPAGE3);
	glcd_blank_page(LPAGE4);
	glcd_blank_page(LPAGE5);
	glcd_blank_page(LPAGE6);
	glcd_blank_page(LPAGE7);

	draw_text_bmp((INT8U *)"Add Item",44,TPAGE0,MyFont,1);
	draw_text_bmp((INT8U *)"No UPC Match in Database",16,TPAGE1,MyFont,1);
	draw_text_bmp((INT8U *)"Would you like to ",1,TPAGE2,MyFont,1);
	draw_text_bmp((INT8U *)"Add UPC to database?",1,TPAGE3,MyFont,1);
	draw_text_bmp((INT8U *)"Try Again?",1,TPAGE4,MyFont,1);
	draw_text_bmp((INT8U *)"Or Go Back To Main Menu?",1,TPAGE5,MyFont,1);

	draw_line(1,PAGE6,128,PAGE6,1);
	draw_line(31,49,31,64,1);
	draw_line(63,49,63,64,1);
	draw_line(95,49,95,64,1);
	//F1
	draw_text_bmp((INT8U *)"Main",1,FPAGE6,MyFont,1);
	draw_text_bmp((INT8U *)"Menu",1,FPAGE7,MyFont,1);
	//F3
	draw_text_bmp((INT8U *)" Add To",65,FPAGE6,MyFont,1);
	draw_text_bmp((INT8U *)"Database",65,FPAGE7,MyFont,1);
	//F4
	draw_text_bmp((INT8U *)" Try ",97,FPAGE6,MyFont,1);
	draw_text_bmp((INT8U *)"Again",97,FPAGE7,MyFont,1);

	//last two pages with F1=Main Menu, F2= ~blank, F3 = Add to database, F4 = Try again
}

void AddMsgNewExp(void){
	draw_text_bmp((INT8U *)"Add Item",44,TPAGE0,MyFont,1);
	draw_text_bmp((INT8U *)"Please Enter Expiration Date",16,TPAGE1,MyFont,1);
	draw_text_bmp((INT8U *)"In Format MM/DD/YYYY",1,TPAGE2,MyFont,1);

	//last two pages with F1=Main Menu, F2= ~blank, F3 = Add to database, F4 = Try again
}
void RemoveMsg(void){
	glcd_blank_pagexy(LPAGE1,34,95);
	glcd_blank_page(LPAGE1);
	glcd_blank_page(LPAGE2);
	glcd_blank_page(LPAGE3);
	glcd_blank_page(LPAGE4);
	glcd_blank_page(LPAGE5);
	glcd_blank_page(LPAGE6);
	glcd_blank_page(LPAGE7);
	draw_text_bmp((INT8U *)"Remove Item",44,TPAGE0,MyFont,1);
	draw_text_bmp((INT8U *)"Please use Barcodescanner Or Keyboard",16,TPAGE2,MyFont,1);
	draw_line(1,PAGE6,128,PAGE6,1);
	draw_line(31,49,31,64,1);
	draw_line(63,49,63,64,1);
	draw_line(95,49,95,64,1);
	//F1
	draw_text_bmp((INT8U *)"Main",1,FPAGE6,MyFont,1);
	draw_text_bmp((INT8U *)"Menu",1,FPAGE7,MyFont,1);
	//F2
	//draw_text_bmp((INT8U *)"Remove",33,FPAGE6,MyFont,1);
	//draw_text_bmp((INT8U *)" Item",33,FPAGE7,MyFont,1);
	//F3
	draw_text_bmp((INT8U *)" Add ",65,FPAGE6,MyFont,1);
	draw_text_bmp((INT8U *)" Item",65,FPAGE7,MyFont,1);
	//F4
	draw_text_bmp((INT8U *)" View ",97,FPAGE6,MyFont,1);
	draw_text_bmp((INT8U *)" Stock",97,FPAGE7,MyFont,1);draw_text_bmp((INT8U *)"to enter UPC",16,TPAGE3,MyFont,1);

	//inverted box on page 4
	//last two pages with F1=Main Menu, F2=Remove Item, F3=Add By Name, F4=View Inv
}

void RemoveMsgFound(void){
	glcd_blank_page(LPAGE1);
	glcd_blank_page(LPAGE2);
	glcd_blank_page(LPAGE3);
	glcd_blank_page(LPAGE4);
	glcd_blank_page(LPAGE5);
	glcd_blank_page(LPAGE6);
	glcd_blank_page(LPAGE7);
	draw_text_bmp((INT8U *)"Remove Item",44,TPAGE0,MyFont,1);
	draw_text_bmp((INT8U *)"Found!",16,TPAGE2,MyFont,1);
	//insert item name after fount on page2
	draw_text_bmp((INT8U *)"Please Enter Expiration Date",1,TPAGE3,MyFont,1);
	draw_text_bmp((INT8U *)"In Format MM/DD/YYYY",1,TPAGE4,MyFont,1);
	//inverted box on page 5
	draw_line(1,PAGE6,128,PAGE6,1);
	draw_line(31,49,31,64,1);
	draw_line(63,49,63,64,1);
	draw_line(95,49,95,64,1);
}

void InvMsg(void){
	glcd_blank_pagexy(LPAGE1,34,95);
	glcd_blank_page(LPAGE1);
	glcd_blank_page(LPAGE2);
	glcd_blank_page(LPAGE3);
	glcd_blank_page(LPAGE4);
	glcd_blank_page(LPAGE5);
	glcd_blank_page(LPAGE6);
	glcd_blank_page(LPAGE7);
	draw_text_bmp((INT8U *)"View Inventory",36,TPAGE0,MyFont,1);
	draw_line(1,PAGE6,128,PAGE6,1);
	draw_line(31,49,31,64,1);
	draw_line(63,49,63,64,1);
	draw_line(95,49,95,64,1);
	//F1
	draw_text_bmp((INT8U *)"Main",1,FPAGE6,MyFont,1);
	draw_text_bmp((INT8U *)"Menu",1,FPAGE7,MyFont,1);
	//F2
	//draw_text_bmp((INT8U *)"Remove",33,FPAGE6,MyFont,1);
	//draw_text_bmp((INT8U *)" Item",33,FPAGE7,MyFont,1);
	//F3
	//draw_text_bmp((INT8U *)" Add ",65,FPAGE6,MyFont,1);
	//draw_text_bmp((INT8U *)" Item",65,FPAGE7,MyFont,1);
	//F4
	//draw_text_bmp((INT8U *)" View ",97,FPAGE6,MyFont,1);
	//draw_text_bmp((INT8U *)" Stock",97,FPAGE7,MyFont,1);draw_text_bmp((INT8U *)"to enter UPC",16,TPAGE3,MyFont,1);

	//inverted box on page 4
	//last two pages with F1=Main Menu, F2=Remove Item, F3=Add By Name, F4=View Inv
}
void InvArrow(void){
	draw_text_bmp((INT8U *)"->",33,FPAGE6,MyFont,1);
}

void InvSelectMsg(INT8U item){
	INT8U quanstring[5];
	draw_text_bmp((INT8U *)"Name",1,FPAGE1,MyFont,1);
	draw_text_bmp(ItemBlock1[item].Discription,50,FPAGE1,MyFont,1);
	draw_text_bmp((INT8U *)"Expiration",1,FPAGE2,MyFont,1);
	draw_text_bmp(ItemBlock1[item].Experation,50,FPAGE2,MyFont,1);
	draw_text_bmp((INT8U *)"TimeStamp:",1,FPAGE3,MyFont,1);
	draw_text_bmp(ItemBlock1[item].Timestamp,50,FPAGE3,MyFont,1);
	draw_text_bmp((INT8U *)"Quan:",1,FPAGE4,MyFont,1);
	int_to_string(ItemBlock1[item].Quantity,quanstring);
	string_rev(quanstring);
	//draw_text_char(quanstring,1,FPAGE4,MyFont,1);
	draw_text_bmp(quanstring,50,FPAGE4,MyFont,1);
	draw_text_bmp((INT8U *)"UPC:",1,FPAGE5,MyFont,1);
	draw_text_bmp(ItemBlock1[item].UPC,50,FPAGE5,MyFont,1);
	draw_line(1,PAGE6,128,PAGE6,1);
	draw_line(31,PAGE6,31,64,1);
	draw_line(63,PAGE6,63,64,1);
	draw_line(95,PAGE6,95,64,1);
	draw_text_bmp((INT8U *)"Back",1,FPAGE7,MyFont,1);

}
