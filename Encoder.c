/*
 * Encoder.c
 *
 *  Created on: Apr 17, 2013
 *      Author: AGV-EET
 */

#include "Encoder.h"

INT8U	ScrollCnt=0;
INT16U	Val=0;

void
EncoderIntHandler(void){
	GPIOPinIntClear(ENCODER_GPIO_BASE,ENCODA);
	//System_printf("Encoder!\n");
	//System_flush();
	Val=GPIO_PORTA_DATA_R & ENCODB;
	if(Val==0){
		if(ScrollCnt<MAXSCROLL){
			ScrollCnt++;
			System_printf("Count = %d \n",ScrollCnt);
			System_flush();
		}else{}
	}
	else{
		if(ScrollCnt>0){
					ScrollCnt--;
					System_printf("Count = %d \n",ScrollCnt);
					System_flush();
				}else{}
	}

}

void EncoderInit(void){
	//SysCtlPeripheralEnable(ENCODER_GPIO_PERIP);
	GPIOPinTypeGPIOInput(ENCODER_GPIO_BASE,ALL_LINES);
	GPIO_PORTE_DATA_R = 0x00;
	GPIOIntTypeSet(ENCODER_GPIO_BASE,ENCODA,GPIO_RISING_EDGE);
	//GPIOPortIntRegister(ENCODER_GPIO_BASE,EncoderIntHandler);
	GPIOPinIntEnable(ENCODER_GPIO_BASE,ENCODA);
}
