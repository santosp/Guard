/*
 * Clock.h
 *
 *  Created on: Mar 30, 2013
 *      Author: Alix
 */

#ifndef CLOCK_H_
#define CLOCK_H_

//Includes
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/timer.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom.h"
#include "st7565.h"
#include "st7565-config.h"

#include "driverlib/gpio.h"
#include "graphics.h"
#include "Graphics_Bmp.h"


#include "Code_Standards.h"


//Private module defines
typedef struct{
	INT8U hr;
	INT8U min;
	INT8U sec;
}TIME;

#define SYSTICKS_PER_SEC  1

//Public Function Declarations
extern void ClockInit(void);
extern void TimeGet(TIME *ltime);
extern void TimeSet(TIME *ltime);

#endif /* CLOCK_H_ */
