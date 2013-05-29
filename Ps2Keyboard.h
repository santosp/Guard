/*
 * Ps2Keyboard.h
 *
 *  Created on: Mar 27, 2013
 *      Author: AGV-EET
 */

#ifndef PS2KEYBOARD_H_
#define PS2KEYBOARD_H_

#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Task.h>

#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "graphics.h"

#include "driverlib/sysctl.h"
#include "Code_Standards.h"
#include "driverlib/ssi.h"
#include "inc/lm4f120h5qr.h"


#include "Font.h"
#include "Graphics_Bmp.h"
#include "scancodes.h"



#define RESEND      0xFE
#define ACK         0xFA
#define BREAKCHAR   0xF0
#define LEFTSHIFT   0x12
#define RIGHTSHIFT  0x59
#define CTRLKEY     0x14
#define ALTKEY      0x11
#define CAPSLOCK    0x58
#define	NUMLOCK     0x77
#define SCROLLLOCK  0x7E
#define DOUBLECODE  0xE1
#define NONUMCODE   0xE0

#define KBLED_ON 1
#define KBLED_OFF 0

#define KBUFFSIZE 4

#define CAPSLED 0x04
#define NUMLED  0x01

#define NUM_SSI_DATA 11
#define K_STARTBIT    1
#define K_PARITYBIT  10
#define K_STOPBIT    11


typedef enum{PS2START,PS2DATA,PS2PARITY,PS2STOP}PS2STATE;

extern void KeyboardInit(void);
extern INT8U KeyPend(INT16U tout);

#endif /* PS2KEYBOARD_H_ */
