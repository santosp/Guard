/*
 * Clock.c
 *
 *  Created on: Mar 30, 2013
 *      Author: Alix
 */
//Includes
#include "Clock.h"
#include <xdc/runtime/System.h>
#include <xdc/runtime/Error.h>
#include <ti/sysbios/gates/GateMutexPri.h>

static TIME Time={2,00,00};
//static INT8U temp_time_string[10];
//GateMutexPri_Handle timemutex;
//Error_Block eb;
//IArg gatekey;


//Function ClockInit();
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

//*****************************************************************************
//
// Called by the NVIC as a result of SysTick Timer rollover interrupt flag
//
// Checks buttons and calls AppButtonHandler to manage button events.
// Tracks time and auto mode color stepping.  Calls AppRainbow to implement
// RGB color changes.
//
//*****************************************************************************
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

void TimeGet(TIME *ltime){
	//mutexpend
	//gatekey = GateMutexPri_enter(timemutex);
	*ltime=Time;
	//GateMutexPri_leave(timemutex,gatekey);

}

void TimeSet(TIME *ltime){
	//gatekey = GateMutexPri_enter(timemutex);
	*ltime=Time;
	//GateMutexPri_leave(timemutex,gatekey);
}


