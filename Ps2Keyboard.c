/*
 * Ps2Keyboard.c
 *
 *  Created on: Mar 27, 2013
 *      Author: AGV-EET
 */
#include "Ps2Keyboard.h"
#define NUM_SSI_DATA 11
INT8U temp_count=0;
INT8U temp_count_string[4];
unsigned long ulDataRx[NUM_SSI_DATA];
unsigned long Data=0;

extern Semaphore_Handle KeySem;
extern Semaphore_Handle DataSem;
INT8U	KeyBuf[KBUFFSIZE];	//PS2 Keyboard buffer, the register to store characters key in
INT8U	KeyIn;				//Index into PS/2 key buf where next scan code will be inserted
INT8U	KeyOut;				//Index into PS/2 key buf where next scan code will be removed
INT8U	KeyRead;			//Number of keys read from the PS/2 keyboard
INT8U 	KeyBuffer=0;
/*======================================================================*/
void
FSSIntHandler(void){
	GPIOPinIntClear(GPIO_PORTB_BASE,GPIO_PIN_4);
	GPIOPinIntDisable(GPIO_PORTB_BASE,GPIO_PIN_4);
	//SSIIntClear(SSI2_BASE,SSI_RXFF);

#if 1
	//BIT_CLR(GPIO_PORTB_BASE,GPIO_PIN_3);
	while(SSI2_DR_R&01!=1){}//Wait till data
	//Semaphore_post(DataSem);
	Data=SSI2_DR_R;
	SSI2_DR_R=0x00000000;
	Data&=0x03FC;
	Data>>=2;
	Data=Byte_Reverse((INT8U)Data);
	if(Data>0){
	Decode((INT8U)Data);
	Data=0;
	}else{/*Do nothing*/};
#endif
	GPIOPinIntEnable(GPIO_PORTB_BASE,GPIO_PIN_4);
}
/*======================================================================*/
void KeyboardInit(void){
#if 0
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

	GPIOPinTypeGPIOInput(GPIO_PORTA_BASE,GPIO_PIN_6);
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,GPIO_PIN_7);
	GPIOIntTypeSet(GPIO_PORTA_BASE,GPIO_PIN_6,GPIO_RISING_EDGE);
	GPIOPortIntRegister(GPIO_PORTA_BASE,KeyboardIntHandler);
	GPIOPinIntEnable(GPIO_PORTA_BASE,GPIO_PIN_6);
#endif
    //Initializing the pins
	SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI2);
    //Enable Ports for use
	//SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	// Connect SPI to PA2 (clock) and PA5(TX)
	GPIOPinConfigure(GPIO_PB4_SSI2CLK);
	GPIOPinConfigure(GPIO_PB6_SSI2RX);
	GPIOPinConfigure(GPIO_PB7_SSI2TX);
	GPIOPinConfigure(GPIO_PB5_SSI2FSS);
	GPIOPinTypeSSI(GPIO_PORTB_BASE, GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_5);
	// Configure SSI0
	//
	SSIConfigSetExpClk(SSI2_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_3, SSI_MODE_SLAVE, SysCtlClockGet()/2, 0x09);
	//
	// Enable the SSI module.
	//
	SSIEnable(SSI2_BASE);
	GPIOIntTypeSet(GPIO_PORTB_BASE,GPIO_PIN_4,GPIO_FALLING_EDGE);

	GPIOPinIntEnable(GPIO_PORTB_BASE,GPIO_PIN_4);

}


/*======================================================================*/
INT8U Decode(INT8U sc)
{
  static INT8U keyisup=FALSE, shift = FALSE,capslock=FALSE;//, mode = 0;
  INT8U i=0;
  INT8U keypress=0;

    if (!keyisup)                   /* Last data received was the up-key identifier */
    {
      switch (sc)
        {
        case BREAKCHAR :        /*  The up-key identifier */
			keyisup = TRUE;
			break;

        case NONUMCODE :	/* No valid key yet*/
			//keyisup = TRUE;
			break;

        case LEFTSHIFT :
			shift = TRUE;
			break;

        case RIGHTSHIFT:
			shift = TRUE;
			break;

        case 0x58: //caps lock
			capslock=!capslock;
			break;
        default:
			if (!shift && !capslock){//lowercase & #s
				// do a table look-up
				for (i = 0; unshifted[i][0]!=sc && unshifted[i][0]; i++);
				if (unshifted[i][0] == sc)
				{
					PutKeyBuf((unshifted[i][1]));
					//keypress = unshifted[i][1];
				}
			}
			else if (shift && !capslock){//uppercase & symbols
			    /* look-up */
				for (i = 0; shifted[i][0]!=sc && shifted[i][0]; i++);
				if (shifted[i][0] == sc)
				{
					PutKeyBuf((shifted[i][1]));
					//keypress = shifted[i][1];
					shift=0;
				}
			}
			else if (!shift && capslock){//uppercase & #s
				for (i = 0; shifted[i][0]!=sc && shifted[i][0]; i++);
                if((shifted[i][0] == sc) &&(i<=28&&i>=53)){
                    PutKeyBuf((shifted[i][1]));
                	//keypress = shifted[i][1];
                    shift=0;
                }
                else{
                    PutKeyBuf((unshifted[i][1]));
                	//keypress = unshifted[i][1];
                    shift=0;
                }
			}
			else{//lowercase & symbols
                for (i = 0; shifted[i][0]!=sc && shifted[i][0]; i++);
                if((shifted[i][0] == sc) &&(i<=28&&i>=53)){
                    PutKeyBuf((unshifted[i][1]));
                	//keypress = unshifted[i][1];
                    shift=0;
                }
                else{
                    PutKeyBuf((shifted[i][1]));
                	//keypress = shifted[i][1];
                    shift=0;
                }
			}
			break;
         }// End of Switch
    }// End of IF
    else
    {
		keyisup = FALSE;
		switch (sc)
        {
			case LEFTSHIFT :
				break;
			case RIGHTSHIFT:
			shift = FALSE;
			break;
        }
    }
    //return keypress;
}//End Of Decode
/*======================================================================*/
/*  Type: Function - Private
	Name: PutKeyBuf
	 - Puts valid key into buffer
*/
void PutKeyBuf (INT8U key)
{
	if (KeyRead < KBUFFSIZE)  		//make sure that we don't overflow the buffer
    {
      KeyRead++;							//Increment the number of keys read
      KeyBuf[KeyIn++] = key;		//Store the scan code into the buffer
      if (KeyIn >= KBUFFSIZE)  	//Adjust index to the next scan code to put in buffer
        {
          KeyIn = 0;
        }else{}
    }else{}
}

INT8U GetKey(void)// public function, can be called from main polling loop
{
	INT8U key=0;
  if (KeyRead > 0)
    {
      KeyRead--;			/* Decrement the number of keys in the buffer */
      key = KeyBuf[KeyOut];	/* Get scan code from the buffer */
      KeyOut++;
      if (KeyOut >= KBUFFSIZE)
        {
          KeyOut = 0;
        }

    } else {
        return (0x00);					/* No scan codes in buffer, return -1 */
    }
  return (key);						/* return the scan code of the key pressed */
}

INT8U KeyPend(INT16U tout){
	Bool timeout;
	INT8U key=0;
	timeout=Semaphore_pend(KeySem,tout);
	if(timeout){
		return 0;
	}
	else{
		key=KeyBuffer;
		KeyBuffer=0;
		return key;
	}
}

#if 1
Void KeyTask(UArg a0, UArg a1){
	INT8U key;
	while(1){
		Task_sleep(10);
		key = GetKey();
		if(key>0){
			KeyBuffer = key;
			Semaphore_post(KeySem);
		}
	}

}
#endif
INT8U Byte_Reverse(INT16U org){
	INT8U temp=0,x=0,temp_org=0;
	temp_org=org;
	for(x=0;x<8;x++){
		temp+= temp_org&0x01;
		if(x!=7){
			temp<<=1;
			temp_org>>=1;
		}else{}
	}
	return temp;
}
INT8U KeyScan(void){
	INT16U Data=0;
	Semaphore_pend(DataSem,0);
	//if(SSI2_RIS_R&0x04){
		//Data = SSI2_DR_R&0x07FF;
		//Data = SSIDataGetNonBlocking(SSI2_BASE,(INT32U *)SSI2_DR_R);
		//SSI2_DR_R = 0x0000 & 0x07FF;
		//Data&=0x03FC;
		//Data>>=2;
		//Data=Byte_Reverse((INT8U)Data);
	//}
	if(Data==0||Data>0x7E){
		//Data = Decode((INT8U)Data);
		Data=0;
	}else{
		Data = Decode((INT8U)Data);
	}
	return Data;
}
