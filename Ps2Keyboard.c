/*
 * Ps2Keyboard.c
 *
 *  Created on: Mar 27, 2013
 *      Author: Paul Santos
 */
#include "Ps2Keyboard.h"


//INT8U temp_count=0;
//INT8U temp_count_string[4];

/* Private Function Prototypes */
static INT8U GetKey(void);
static void PutKeyBuf(INT8U c);
static void Decode(INT8U sc);

/* Include Semaphore to module */
extern Semaphore_Handle KeySem;
//extern Semaphore_Handle DataSem;//For use with SPI

/* Global variables*/
static INT8U	KeyBuf[KBUFFSIZE];	//PS2 Keyboard buffer, the register to store characters key in
static INT8U	KeyIn;				//Index into PS/2 key buf where next scan code will be inserted
static INT8U	KeyOut;				//Index into PS/2 key buf where next scan code will be removed
static INT8U	KeyRead;			//Number of keys read from the PS/2 keyboard
static INT8U 	KeyBuffer=0;

/*Globals Needed for interrupt handler*/
static INT8U	Clkstat,Datstat;	//State of the clock and Data lines
static INT8U 	Paritystat;			//Statis of Parity bit
static INT8U 	Datain;				//Incoming bit status
static INT8U 	BitCount=0;			//Index to keep track of bits in a message

/*======================================================================*/
/*  Type: Function - Public
	Name: ClockInit
	 - Initialization function that sets up the clock module
*/
void
FSSIntHandler(void){

	GPIOPinIntClear(GPIO_PORTB_BASE,GPIO_PIN_4);
	Clkstat = GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_4);//check CLK pin state;
	Datstat = GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_6);//check DAT pin state;
	BitCount++;
	if (BitCount==K_STARTBIT){
		if (Datstat || Clkstat)	BitCount=0;
		Datain=0;
		Paritystat=0;
	}
	else if (BitCount==K_PARITYBIT){
		Paritystat = Datstat;
	}
	else if (BitCount==K_STOPBIT){
		Decode(Datain);
		BitCount=0;
	}
	else{
	  // For all bits from 2, 3...9 (total 8-bit)
		Datain= Datain >> 1;
	  if (Datstat)Datain = Datain | 0x80;
	}

#if 0
	//GPIOPinIntDisable(GPIO_PORTB_BASE,GPIO_PIN_4);
	SSIIntClear(SSI2_BASE,SSI_RXFF);


	//BIT_CLR(GPIO_PORTB_BASE,GPIO_PIN_3);
	while(SSI2_DR_R&01!=1){}//Wait till data
	//Semaphore_post(DataSem);
	Data=SSI2_DR_R;
	//SSI2_DR_R=0x7FFF;
	//SSI2_DR_R=0xFFFF;
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
/*  Type: Function - Public
	Name: KeyboardInit
	 - Initialization function that sets up the Keyboard module
*/

void KeyboardInit(void){

#if 1

	//SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	GPIOPinTypeGPIOInput(GPIO_PORTB_BASE,GPIO_PIN_4|GPIO_PIN_6);
	GPIOIntTypeSet(GPIO_PORTB_BASE,GPIO_PIN_4,GPIO_RISING_EDGE);
	//GPIOPortIntRegister(GPIO_PORTA_BASE,KeyboardIntHandler);

#else
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
	SSIIntEnable(SSI2_BASE,SSI_RXFF);


	SSIEnable(SSI2_BASE);
#endif
	GPIOIntTypeSet(GPIO_PORTB_BASE,GPIO_PIN_4,GPIO_FALLING_EDGE);
	GPIOPinIntEnable(GPIO_PORTB_BASE,GPIO_PIN_4);
}


/*======================================================================*/
/*  Type: Function - Private
	Name: Decode
	 - Decodes the PS/2 scancode to its propper ascii character
*/
void Decode(INT8U sc){
	static INT8U keyisup=FALSE, shift = FALSE,capslock=FALSE;//, mode = 0;
	INT8U i=0;
	if (!keyisup){                   /* Last data received was the up-key identifier */
		switch (sc){

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
				if (unshifted[i][0] == sc){

					PutKeyBuf((unshifted[i][1]));
				}
			}
			else if (shift && !capslock){//uppercase & symbols
				/* look-up */
				for (i = 0; shifted[i][0]!=sc && shifted[i][0]; i++);
				if (shifted[i][0] == sc){
					PutKeyBuf((shifted[i][1]));
					shift=0;
				}
			}
			else if (!shift && capslock){//uppercase & #s
				for (i = 0; shifted[i][0]!=sc && shifted[i][0]; i++);
				if((shifted[i][0] == sc) &&(i<=28&&i>=53)){
					PutKeyBuf((shifted[i][1]));
					shift=0;
				}
				else{
					PutKeyBuf((unshifted[i][1]));
					shift=0;
				}
			}
			else{//lowercase & symbols
				for (i = 0; shifted[i][0]!=sc && shifted[i][0]; i++);
				if((shifted[i][0] == sc) &&(i<=28&&i>=53)){
					PutKeyBuf((unshifted[i][1]));
					shift=0;
				}
				else{
					PutKeyBuf((shifted[i][1]));
					shift=0;
				}
			}
			break;
		}// End of Switch
	}// End of IF
	else
	{
		keyisup = FALSE;
		switch (sc){
			case LEFTSHIFT :
				shift = FALSE;
				break;
			case RIGHTSHIFT:
				shift = FALSE;
				break;
		}
	}
}//End Of Decode
/*======================================================================*/
/*  Type: Function - Private
	Name: PutKeyBuf
	 - Puts valid key into buffer
*/
void PutKeyBuf (INT8U key){
	if (KeyRead < KBUFFSIZE){  		//make sure that we don't overflow the buffer
		KeyRead++;							//Increment the number of keys read
		KeyBuf[KeyIn++] = key;		//Store the scan code into the buffer
		if (KeyIn >= KBUFFSIZE){  	//Adjust index to the next scan code to put in buffer
			KeyIn = 0;
		}else{/*Do nothing*/}
	}else{/*Do nothing*/}
}
/*======================================================================*/
/*  Type: Function - Private
	Name: GetKey
	 - Puts valid key into buffer
*/
INT8U GetKey(void){// public function, can be called from main polling loop
	INT8U key=0;
	if (KeyRead > 0){
		KeyRead--;			/* Decrement the number of keys in the buffer */
		key = KeyBuf[KeyOut];	/* Get scan code from the buffer */
		KeyOut++;
		if (KeyOut >= KBUFFSIZE){
			KeyOut = 0;
		}
	}else{
		return (0x00);					/* No scan codes in buffer, return -1 */
	}
	return (key);						/* return the scan code of the key pressed */
}
/*======================================================================*/
/*  Type: Function - Public
	Name: KeyPend
	 - Public function that uses a private semaphore to wait for a keypress
	 or a timeout, if there is a timeout, it returns a zero.
*/
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
/*======================================================================*/
/*  Type: Task - Private
	Name: KeyTask
	 - Pulls Valid Key, checks to see if it greater then 0, then posts a semaphore
*/
Void KeyTask(UArg a0, UArg a1){
	INT8U key;
	while(1){
		Task_sleep(10);
		key = GetKey();
		if(key>0){
			KeyBuffer = key;
			Semaphore_post(KeySem);
			key=0;
		}
	}

}
