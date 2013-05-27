/*
 *  ======== main.c ========
 */

#include <xdc/std.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>

#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/gates/GateMutexPri.h>




#include "Encoder.h"
#include "Buttons.h"
#include "Graphics_Bmp.h"
#include "Font.h"
#include "st7565.h"
#include "Code_Standards.h"
#include "Clock.h"
#include "Ps2Keyboard.h"
/*=======*/
//Globals
UISTATEINFO StateInfo={REMOVE,TRUE}; // NEED TO START IN WELCOME not MAIN
UISTATE LastState=MAIN;


/*=======*/

/*
 *  ======== taskFxn ========
 */


Void taskFxn(UArg a0, UArg a1)
{
	while(1){
    System_printf("enter taskFxn()\n");
	System_flush();
    Task_sleep(10);
    draw_text_bmp((INT8U *)"Text!",8,8,MyFont,1);
    glcd_refresh();
    //glcd_command(GLCD_CMD_ALL_ON);
    System_printf("exit taskFxn()\n");
    System_flush();
	}
}
/*
 *  ======== taskFxn ========
 */
Void UiTask(UArg a0, UArg a1)
{
	INT8U key=0;
	INT8U upcbuffer[12]={'0','0','0','0','0','0','0','0','0','0','0',0};
	INT8U upccount=0;
	while(1){
		//poll buttons
		switch(StateInfo.UserState){
			case WELCOME:
				if(StateInfo.StateInit==TRUE){
				//draw_text_bmp((INT8U *)"Welcome To The Grocery Guard System",16,16,MyFont,1);
				//draw_text_bmp((INT8U *)"Please Enter The Current Date in HH:MMPM/AM,MM/DD/YYYY Format",16,24,MyFont,1);
				//draw_text_bmp((INT8U *)"Ex) 2:30PM , May 5th 2013",16,32,MyFont,1);
				//draw_text_bmp((INT8U *)"02:30PM , 05/05/2013 ",16,40,MyFont,1);
				StateInfo.StateInit=FALSE;
				}
				else{//Do Rest of State code
					//KeyPend(timeout)
				}
				//Start KeyTask

			break;
			case MAIN:
				if(StateInfo.StateInit==TRUE){
					//Kill/Start tasks required
					StateInfo.StateInit=FALSE;
				}
				else{//Do Rest of State code
					//KeyPend(timeout)
					draw_text_bmp((INT8U *)"MAIN STATE ",16,40,MyFont,1);
				}
			break;
			case ADD:
				if(StateInfo.StateInit==TRUE){
					//Kill/Start tasks required
					StateInfo.StateInit=FALSE;
				}
				else{//Do Rest of State code
					key=KeyPend(1000);
					if(key>0){
						upcbuffer[upccount]=key;
						upccount++;
						draw_text_bmp(upcbuffer,16,48,MyFont,1);
					}
					draw_text_bmp((INT8U *)"ADD STATE ",16,40,MyFont,1);
				}
			break;
			case REMOVE:
				if(StateInfo.StateInit==TRUE){
					//Kill/Start tasks required
					StateInfo.StateInit=FALSE;
				}
				else{key=KeyPend(10);
					if(key>0&&key<0x7E){
						upcbuffer[upccount]=key;
						upccount++;
						draw_text_bmp(upcbuffer,16,48,MyFont,1);
					}
					if(upccount>10){
						upccount=0;
					}
					key=0;
					draw_text_bmp((INT8U *)"REMOVE STATE ",16,40,MyFont,1);
				}
			break;
			case INV:
				if(StateInfo.StateInit==TRUE){
					//Kill/Start tasks required
					StateInfo.StateInit=FALSE;
					draw_text_bmp((INT8U *)"INV STATE ",16,40,MyFont,1);
				}
				else{//Do Rest of State code
					//KeyPend(timeout)
				}
			break;
			default:
			break;
		}

	}
}
/*
 *  ======== main ========
 */
Void main()
{ 
    /*
     * use ROV->SysMin to view the characters in the circular buffer
     */
    System_printf("enter main()\n");
    System_flush();

    ClockInit();
	//EncoderInit();
    glcd_init();
    glcd_command(GLCD_CMD_DISPLAY_ON);
	glcd_blank();
	ButtonsInit();
	KeyboardInit();

    BIOS_start();        /* enable interrupts and start SYS/BIOS */
}

