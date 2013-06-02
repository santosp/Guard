//*****************************************************************************
//
// buttons.c - Evaluation board driver for push buttons.
//
// Copyright (c) 2012 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 9453 of the EK-LM4F120XL Firmware Package.
//
//*****************************************************************************
#include <xdc/std.h>

#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>

#include <ti/sysbios/knl/Task.h>

//#include <ti/sysbios/knl/Semaphore.h>

#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "Code_Standards.h"
#include "Graphics_Bmp.h"
#include "Font.h"
#include "st7565.h"
#include "Clock.h"
#include "Ps2Keyboard.h"
/*  Include the State info so buttons can change the states */
extern UISTATEINFO StateInfo;


void int_to_string(INT16U x, INT8U *string);
INT8U scrollcountstring[5];
TIME TimeOfDay={0,0,0};

/*======================================================================*/
/*  Type: Task - Private
	Name: StateTask
	 - Pends on a semaphore that is posted when a function key is pressed
	 - Changes the user states according to the F key that is pressed
*/
/*======================================================================*/
Void StateTask(UArg a0, UArg a1){
	INT8U key=0;
	while(1){
		//buttondata = ButtonsPoll(0,0);
		//pend on state sem
		key=StatePend(BIOS_WAIT_FOREVER);

		switch(StateInfo.UserState){
			case WELCOME:
				//Do Nothing because we want user to set the time
			break;//End of INIT State
			/*======================================================================*/
			case MAIN:
				switch(key){
					case F1:
						//Change State
						////gatetKey = GateMutexPri_enter(gatemutexPri);//Dont Think I need Button Mutex
						StateInfo.UserState = MAIN;
						//set re-initialize variable
						StateInfo.StateStatus = INIT;
						////GateMutexPri_leave(gateMutexPri,gateKey);

					break;
					/*-----------------------------------------------------------*/
					case F2:
						//code
						StateInfo.UserState = REMOVE;
						//set re-initialize variable
						StateInfo.StateStatus = INIT;
					break;
					/*-----------------------------------------------------------*/
					case F3:
						//code
						//change state
						StateInfo.UserState = ADD;
						//set re-initialize variable
						StateInfo.StateStatus = INIT;
					break;
					/*-----------------------------------------------------------*/
					case F4:
						//code
						//change state
						StateInfo.UserState = INV;
						//set re-initialize variable
						StateInfo.StateStatus = INIT;
					break;
					/*-----------------------------------------------------------*/
					default:
					break;
				}
			break;//End of MAIN State
			/*======================================================================*/

			case ADD:
				switch (StateInfo.StateStatus){
				case INIT:
				case GETUPC:
				case INVALID:
				case FIND:
					switch(key){
						case F1:
							//Change State
							////gatetKey = GateMutexPri_enter(gatemutexPri);//Dont Think I need Button Mutex
							StateInfo.UserState = MAIN;
							//set re-initialize variable
							StateInfo.StateStatus = INIT;
							////GateMutexPri_leave(gateMutexPri,gateKey);

						break;
						/*-----------------------------------------------------------*/
						case F2:
							//code
							StateInfo.UserState = REMOVE;
							//set re-initialize variable
							StateInfo.StateStatus = INIT;
						break;
						/*-----------------------------------------------------------*/
						case F3:
							//Do Nothing for now
							//change state
							//StateInfo.UserState = ADD;
							//set re-initialize variable
							//StateInfo.StateStatus = INIT;
						break;
						/*-----------------------------------------------------------*/
						case F4:
							//code
							//change state
							StateInfo.UserState = INV;
							//set re-initialize variable
							StateInfo.StateStatus = INIT;
						break;
						/*-----------------------------------------------------------*/
						default:
						break;
					}
				break;//End of INIT, GETUPC, INVALID and FIND SubState
				/*-----------------------------------------------------------*/
				case FOUND:
					//Do Nothing
				break;//End of FOUND SubState
				/*-----------------------------------------------------------*/
				case NOMATCH:
					switch(key){
						case F1:
							//Change State
							////gatetKey = GateMutexPri_enter(gatemutexPri);//Dont Think I need Button Mutex
							StateInfo.UserState = MAIN;
							//set re-initialize variable
							StateInfo.StateStatus = INIT;
							////GateMutexPri_leave(gateMutexPri,gateKey);

						break;
						/*-----------------------------------------------------------*/
						case F2:
							//Blank so do nothing
						break;
						/*-----------------------------------------------------------*/
						case F3:
							//Add to Database
							//Nothing for now
						break;
						/*-----------------------------------------------------------*/
						case F4:
							//Try again
							//change state
							StateInfo.UserState = ADD;
							//set re-initialize variable
							StateInfo.StateStatus = INIT;
						break;
						/*-----------------------------------------------------------*/
						default:
						break;
					}
				break;//End of NOMATCH SubState
				/*-----------------------------------------------------------*/
				default:
				break;//End of SubState Default
				}//End of StateStatus ADD switch

			break;//End of ADDstate
			/*======================================================================*/

			case REMOVE:
				switch (StateInfo.StateStatus){
				case INIT:
				case GETUPC:
				case INVALID:
				case FIND:
					switch(key){
						case F1:
							//Change State
							////gatetKey = GateMutexPri_enter(gatemutexPri);//Dont Think I need Button Mutex
							StateInfo.UserState = MAIN;
							//set re-initialize variable
							StateInfo.StateStatus = INIT;
							////GateMutexPri_leave(gateMutexPri,gateKey);

						break;
						/*-----------------------------------------------------------*/
						case F2:
							//Do Nothing for now, might add remove by name
							//StateInfo.UserState = REMOVE;
							//set re-initialize variable
							//StateInfo.StateStatus = INIT;
						break;
						/*-----------------------------------------------------------*/
						case F3:
							//change state
							StateInfo.UserState = ADD;
							//set re-initialize variable
							StateInfo.StateStatus = INIT;
						break;
						/*-----------------------------------------------------------*/
						case F4:
							//code
							//change state
							StateInfo.UserState = INV;
							//set re-initialize variable
							StateInfo.StateStatus = INIT;
						break;
						/*-----------------------------------------------------------*/
						default:
						break;
					}
				break;//End of INIT, GETUPC, INVALID and FIND SubState
				/*-----------------------------------------------------------*/
				case FOUND:
					//Do Nothing
				break;//End of FOUND SubState
				/*-----------------------------------------------------------*/
				case NOMATCH:
					switch(key){
						case F1:
							//Change State
							////gatetKey = GateMutexPri_enter(gatemutexPri);//Dont Think I need Button Mutex
							StateInfo.UserState = MAIN;
							//set re-initialize variable
							StateInfo.StateStatus = INIT;
							////GateMutexPri_leave(gateMutexPri,gateKey);

						break;
						/*-----------------------------------------------------------*/
						case F2:
							//Blank so do nothing
						break;
						/*-----------------------------------------------------------*/
						case F3:
							//Add to Database
							//Nothing for now
						break;
						/*-----------------------------------------------------------*/
						case F4:
							//Try again
							//change state
							StateInfo.UserState = ADD;
							//set re-initialize variable
							StateInfo.StateStatus = INIT;
						break;
						/*-----------------------------------------------------------*/
						default:
						break;
					}
				break;//End of NOMATCH SubState
				/*-----------------------------------------------------------*/
				default:
				break;//End of SubState Default
				}//End of StateStatus ADD switch
			break;//End of REMOVE State
			/*======================================================================*/

			case INV:
				switch(key){
					case F1://Back to Main Menu
						//Change State
						////gatetKey = GateMutexPri_enter(gatemutexPri);
						StateInfo.UserState = MAIN;
						//set re-initialize variable
						StateInfo.StateStatus = INIT;
						////GateMutexPri_leave(gateMutexPri,gateKey);

					break;
					/*-----------------------------------------------------------*/
					case F2:
						//Blank so do nothing
					break;
					/*-----------------------------------------------------------*/
					case F3:
						//Blank so do nothing
					break;
					/*-----------------------------------------------------------*/
					case F4:
						//Blank so do nothing
					break;
					/*-----------------------------------------------------------*/
					default:
					break;
				}
			break;//End of INV State
			/*======================================================================*/

			default:
			//Do Nothing
			break;//End of Default
		}//End of Userstate switch





#if 0
		switch(key){
			case F1:
				//code
				//Change State
				////gatetKey = GateMutexPri_enter(gatemutexPri);//Dont Think I need Button Mutex
				StateInfo.UserState = MAIN;
				//set re-initialize variable
				StateInfo.StateStatus = INIT;
				////GateMutexPri_leave(gateMutexPri,gateKey);

			break;

			case F2:
				//code
				StateInfo.UserState = ADD;
				//set re-initialize variable
				StateInfo.StateStatus = INIT;
			break;

			case F3:
				//code
				//change state
				StateInfo.UserState = REMOVE;
				//set re-initialize variable
				StateInfo.StateStatus = INIT;
			break;

			case F4:
				//code
				//change state
				StateInfo.UserState = INV;
				//set re-initialize variable
				StateInfo.StateStatus = INIT;
			break;

			default:
			break;
		}
#endif
	key=0;
	}
}
/*======================================================================*/
/*  Type: Task - Private
	Name: DisplayTask
	 - Deals with displaying the time of day
	 - Also periodically refreshes the display
*/
/*======================================================================*/


Void DisplayTask(UArg a0, UArg a1){
	while(1){
		TimeGet(&TimeOfDay);
		GlcdDispTime(TimeOfDay.hr,TimeOfDay.min,TimeOfDay.sec);
		glcd_refresh();
		Task_sleep(10);
	}
}


