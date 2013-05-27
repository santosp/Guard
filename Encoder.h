/*
 * Encoder.h
 *
 *  Created on: Apr 17, 2013
 *      Author: AGV-EET
 */

#ifndef ENCODER_H_
#define ENCODER_H_



#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "Code_Standards.h"
#include "inc/lm4f120h5qr.h"
#include <xdc/runtime/System.h>

//*****************************************************************************
//
// Defines for the hardware resources used by the pushbuttons.
//
// The switches are on the following ports/pins:
//
// PF4 - Left Button
// PF0 - Right Button
//
// The switches tie the GPIO to ground, so the GPIOs need to be configured
// with pull-ups, and a value of 0 means the switch is pressed.
//
//*****************************************************************************
#define ENCODER_GPIO_PERIP     SYSCTL_PERIPH_GPIOA
#define ENCODER_GPIO_BASE      GPIO_PORTA_BASE

#define NUM_LINES               2
#define ENCODA            		GPIO_PIN_6
#define ENCODB					GPIO_PIN_7

#define ALL_LINES             (ENCODA | ENCODB)



extern void EncoderInit(void);


#endif /* ENCODER_H_ */
