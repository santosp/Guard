/*
 * Encoder.c
 *
 *  Created on: Apr 17, 2013
 *      Author: AGV-EET
 */

#include "Encoder.h"

INT8U Scroll_Cnt=0;
//INT8U Scroll_Cnt_String[4];
long int val=0;
void
EncoderIntHandler(void){
	GPIOPinIntClear(ENCODER_GPIO_BASE,ENCODA);
	//System_printf("Encoder!\n");
	//System_flush();
	val=GPIO_PORTA_DATA_R & ENCODB;
	if(val==0){
		if(Scroll_Cnt<15){
			Scroll_Cnt++;
			//System_printf("Count = %d \n",Scroll_Cnt);
			//System_flush();
		}else{}
	}
	else{
		if(Scroll_Cnt>0){
					Scroll_Cnt--;
					//System_printf("Count = %d \n",Scroll_Cnt);
					//System_flush();
				}else{}
	}

}

void EncoderInit(void){
	SysCtlPeripheralEnable(ENCODER_GPIO_PERIP);
	GPIOPinTypeGPIOInput(ENCODER_GPIO_BASE,ALL_LINES);
	GPIO_PORTA_DATA_R = 0x00;
	GPIOIntTypeSet(ENCODER_GPIO_BASE,ENCODA,GPIO_RISING_EDGE);
	//GPIOPortIntRegister(ENCODER_GPIO_BASE,EncoderIntHandler);
	GPIOPinIntEnable(ENCODER_GPIO_BASE,ENCODA);
}
