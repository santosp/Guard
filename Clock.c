/*
 * Clock.c
 *
 *  Created on: Mar 30, 2013
 *      Author: Alix
 */
//Includes
#include "Clock.h"

/* Sys/Bios specific headers */
#include <xdc/runtime/System.h>
#include <xdc/runtime/Error.h>
#include <ti/sysbios/gates/GateMutexPri.h>

/* Private Global to module that contains master time of day */
static TIME Time={2,00,00};
//static INT8U temp_time_string[10];
//GateMutexPri_Handle timemutex;
//Error_Block eb;
//IArg gatekey;


/*======================================================================*/
/*  Type: Function - Public
	Name: ClockInit
	 - Initialization function that sets up the clock module
*/

void ClockInit(void){

    //  Set the clocking to run directly from the crystal.
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                       SYSCTL_XTAL_16MHZ);
    // Enable the peripherals
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);

	//Setup the timer to a 32 bit periodic timer
	TimerConfigure(TIMER2_BASE,TIMER_CFG_PERIODIC);

	//Set The timer load
	TimerLoadSet(TIMER2_BASE, TIMER_A,SysCtlClockGet());

	//Enable Timer Interrupts
	IntEnable(INT_TIMER1A);
	TimerIntEnable(TIMER2_BASE,TIMER_TIMA_TIMEOUT);

	//Enable Timer
    TimerEnable(TIMER2_BASE,TIMER_A);

    //GateMutexPri_Params gateMutexPri_Params;
    //GateMutexPri_Params_init(&gateMutexPri_Params);
    //timemutex = GateMutexPri_create(&gateMutexPri_Params,&eb);
    //Error_init(&eb);
}

/*======================================================================*/
/*  Type: Interrupt Handler - Private
	Name: Timer0IntHandler
	 - Interrupt that happens every 1 second from timer, increments time
	 then exits
*/
void
Timer0IntHandler(void)
{
    // Clear the timer interrupt
    TimerIntClear(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
    //System_printf("seconds = %d\n",Time.sec);
    //System_flush();
    //gatekey = GateMutexPri_enter(timemutex);
    Time.sec++;
    if(Time.sec==60){
    	Time.sec=0;
    	Time.min++;
    }else{};
    if(Time.min==60){
    	Time.min=0;
    	Time.hr++;
    }else{}
    if(Time.hr==13){
    	Time.hr=1;
    }else{}
   // GateMutexPri_leave(timemutex,gatekey);

}
/*======================================================================*/
/*  Type: Function - Public
	Name: TimeGet
	 - Pulls Time from master time of day
*/

void TimeGet(TIME *ltime){
	//mutexpend
	//gatekey = GateMutexPri_enter(timemutex);
	*ltime=Time;
	//GateMutexPri_leave(timemutex,gatekey);

}
/*======================================================================*/
/*  Type: Function - Public
	Name:TimeSet
	 - Sets the user designated time to master time of day
*/

void TimeSet(TIME *ltime){
	//gatekey = GateMutexPri_enter(timemutex);
	*ltime=Time;
	//GateMutexPri_leave(timemutex,gatekey);
}


