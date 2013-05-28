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

#include "Items.h"
/*=======*/
//Globals
UISTATEINFO StateInfo={REMOVE,INIT}; // NEED TO START IN WELCOME not MAIN
UISTATE LastState=MAIN;


extern INT8U ItemLookUp[][2];
extern ITEMINFO ItemBlock1[25];
/*=======*/

/*
 *  ======== taskFxn ========
 */


Void taskFxn(UArg a0, UArg a1)
{
	while(1){
    //System_printf("enter taskFxn()\n");
	//System_flush();
    Task_sleep(10);
    draw_text_bmp((INT8U *)"Text!",8,8,MyFont,1);
    glcd_refresh();
    //glcd_command(GLCD_CMD_ALL_ON);
    //System_printf("exit taskFxn()\n");
    //SSystem_flush();
	}
}
/*
 *  ======== taskFxn ========
 */
Void UiTask(UArg a0, UArg a1)
{
	INT8U key=0;
	INT8U upcbuffer[12]={0,0,0,0,0,0,0,0,0,0,0,0};
	INT8U upccount=0,inputcount=0,itemfound=0,lookupcount=0,upc_count=0;
	INT8U clearcount=0;
	while(1){
		//poll buttons
		//Task_delete(testTask);
		switch(StateInfo.UserState){
			case WELCOME:
				switch (StateInfo.StateStatus){
				case INIT:
					//Initialize state
					//draw_text_bmp((INT8U *)"Welcome To The Grocery Guard System",16,16,MyFont,1);
					//draw_text_bmp((INT8U *)"Please Enter The Current Date in HH:MMPM/AM,MM/DD/YYYY Format",16,24,MyFont,1);
					//draw_text_bmp((INT8U *)"Ex) 2:30PM , May 5th 2013",16,32,MyFont,1);
					//draw_text_bmp((INT8U *)"02:30PM , 05/05/2013 ",16,40,MyFont,1);
					//draw_text_bmp((INT8U *)"INV STATE ",16,40,MyFont,1);
				break;//End of INIT State
				/*-----------------------------------------------------------*/
				case GETUPC:
				break;//End of GETUPC State
				/*-----------------------------------------------------------*/
				case INVALID:
					////invalid user input, i.e. non number characters,
				break;//End of INVALID state
				/*-----------------------------------------------------------*/
				case FIND:
				break;//End of FIND State
				/*-----------------------------------------------------------*/
				case FOUND:
				break;//End of FOUND State
				/*-----------------------------------------------------------*/
				case NOMATCH:
				break;//End of NOMATCH State
				/*-----------------------------------------------------------*/
				default:
				break;//End of Default
				}//End of StateStatus WELCOME switch

			break;
			/*===============================================================*/
			case MAIN:
				switch (StateInfo.StateStatus){
				case INIT:
					//Initialize state
					//draw_text_bmp((INT8U *)"Welcome To The Grocery Guard System",16,16,MyFont,1);
					//draw_text_bmp((INT8U *)"Please Enter The Current Date in HH:MMPM/AM,MM/DD/YYYY Format",16,24,MyFont,1);
					//draw_text_bmp((INT8U *)"Ex) 2:30PM , May 5th 2013",16,32,MyFont,1);
					//draw_text_bmp((INT8U *)"02:30PM , 05/05/2013 ",16,40,MyFont,1);
					draw_text_bmp((INT8U *)"MAIN STATE ",16,40,MyFont,1);
				break;//End of INIT State
				/*-----------------------------------------------------------*/
				case GETUPC:
				break;//End of GETUPC State
				/*-----------------------------------------------------------*/
				case INVALID:
					////invalid user input, i.e. non number characters,
				break;//End of INVALID state
				/*-----------------------------------------------------------*/
				case FIND:
				break;//End of FIND State
				/*-----------------------------------------------------------*/
				case FOUND:
				break;//End of FOUND State
				/*-----------------------------------------------------------*/
				case NOMATCH:
				break;//End of NOMATCH State
				/*-----------------------------------------------------------*/
				default:
				break;//End of Default
				}//End of StateStatus MAIN switch

			break;//END of MAIN State
			/*===============================================================*/
			case ADD:
				switch (StateInfo.StateStatus){
				case INIT:
					//Initialize state
					draw_text_bmp((INT8U *)"ADD STATE ",16,40,MyFont,1);
					StateInfo.StateStatus = GETUPC;
					draw_text_bmp((INT8U *)"         ",16,24,MyFont,1);// clear found or not space
					draw_text_bmp((INT8U *)"             ",16,48,MyFont,1);//clear upcbuffer space
					for(clearcount=0;clearcount<11;clearcount++){// clear buffer
						upcbuffer[clearcount]=0;
					}
					upccount=0;
				break;//End of INIT State
				/*-----------------------------------------------------------*/
				case GETUPC:
					key=KeyPend(10);
					if(key>0&&key<0x7E){
						upcbuffer[upccount]=key;
						upccount++;
						draw_text_bmp(upcbuffer,16,48,MyFont,1);
					}
					key=0;
					if(upccount>10){
						upccount=0;
						for(inputcount=0;(upcbuffer[inputcount]<='9'&&upcbuffer[inputcount]>='0')&&inputcount<11;inputcount++);
						if(inputcount>10){
							//valid input
							StateInfo.StateStatus=FIND;
						}
						else{
							//invalid input, i.e. non number characters
							StateInfo.StateStatus=INVALID;
							draw_text_bmp((INT8U *)"INVALID ",16,24,MyFont,1);
						}
					}
				break;//End of GETUPC State
				/*-----------------------------------------------------------*/
				case INVALID:
				break;//End of INVALID State
				/*-----------------------------------------------------------*/
				case FIND://Looks for a UPC match
					for(lookupcount=0;(lookupcount<25&&itemfound!=1);lookupcount++){
						if(ItemLookUp[lookupcount][0]>0){
							for(upc_count=0;upcbuffer[upc_count]==ItemBlock1[lookupcount].UPC[upc_count]&&upc_count<11;upc_count++);
							if(upc_count<11){
								//No match
								//Give user option to either re enter or add to inventory
								StateInfo.StateStatus = NOMATCH;
								//draw_text_bmp((INT8U *)"NO Match ",16,24,MyFont,1);
							}
							else{
								//found item
								itemfound=1;
								StateInfo.StateStatus = FOUND;
								draw_text_bmp((INT8U *)"FOUND ",16,24,MyFont,1);
							}
						}
						else{
							//No item of this UPC number
							//Give user option to either re enter or add to inventory
							StateInfo.StateStatus = NOMATCH;
							draw_text_bmp((INT8U *)"NO Match ",16,24,MyFont,1);
						}
					}
				break;//End of Find
				/*-----------------------------------------------------------*/
				case FOUND:
				break;//End of FOUND
				/*-----------------------------------------------------------*/
				case NOMATCH:
				break;//End of NOMATCH
				/*-----------------------------------------------------------*/
				default:
				break;//End of default
				}//End of StateStatus ADD switch
			break;
			/*===============================================================*/
			case REMOVE:
				switch (StateInfo.StateStatus){
				case INIT:
					//Initialize state
					draw_text_bmp((INT8U *)"REMOVE STATE ",16,40,MyFont,1);
					StateInfo.StateStatus = GETUPC;
					draw_text_bmp((INT8U *)"         ",16,24,MyFont,1);// clear found or not space
					draw_text_bmp((INT8U *)"             ",16,48,MyFont,1);//clear upcbuffer space
					for(clearcount=0;clearcount<11;clearcount++){// clear buffer
						upcbuffer[clearcount]=0;
					}
					upccount=0;
				break;//End of INIT State
				/*-----------------------------------------------------------*/
				case GETUPC:
					key=KeyPend(10);
					if(key>0&&key<0x7E){
						upcbuffer[upccount]=key;
						upccount++;
						draw_text_bmp(upcbuffer,16,48,MyFont,1);
					}
					key=0;
					if(upccount>10){
						upccount=0;
						for(inputcount=0;(upcbuffer[inputcount]<='9'&&upcbuffer[inputcount]>='0')&&inputcount<11;inputcount++);
						if(inputcount>10){
							//valid input
							StateInfo.StateStatus=FIND;
						}
						else{
							//invalid input, i.e. non number characters
							StateInfo.StateStatus=INVALID;
							draw_text_bmp((INT8U *)"INVALID ",16,24,MyFont,1);
						}
					}
				break;//End of GETUPC State
				/*-----------------------------------------------------------*/
				case INVALID:
				break;//End of INVALID State
				/*-----------------------------------------------------------*/
				case FIND://Looks for a UPC match
					for(lookupcount=0;(lookupcount<25&&itemfound!=1);lookupcount++){
						if(ItemLookUp[lookupcount][0]>0){
							for(upc_count=0;upcbuffer[upc_count]==ItemBlock1[lookupcount].UPC[upc_count]&&upc_count<11;upc_count++);
							if(upc_count<11){
								//No match
								//Give user option to either re enter or add to inventory
								StateInfo.StateStatus = NOMATCH;
								//draw_text_bmp((INT8U *)"NO Match ",16,24,MyFont,1);
							}
							else{
								//found item
								itemfound=1;
								StateInfo.StateStatus = FOUND;
								draw_text_bmp((INT8U *)"FOUND ",16,24,MyFont,1);
							}
						}
						else{
							//No item of this UPC number
							//Give user option to either re enter or add to inventory
							StateInfo.StateStatus = NOMATCH;
							draw_text_bmp((INT8U *)"NO Match ",16,24,MyFont,1);
						}
					}
				break;//End of FIND State
				/*-----------------------------------------------------------*/
				case FOUND:
				break;//End of FOUND State
				/*-----------------------------------------------------------*/
				case NOMATCH:
				break;//End of NOMATCH State
				/*-----------------------------------------------------------*/
				default:
				break;//End of Default
				}//End of StateStatus REMOVE switch

			break;//End of Remove State
			/*===============================================================*/
			case INV:
				switch (StateInfo.StateStatus){
				case INIT:
					//Initialize state
					draw_text_bmp((INT8U *)"INV STATE ",16,40,MyFont,1);
				break;//End of INIT State
				/*-----------------------------------------------------------*/
				case GETUPC:
				break;//End of GETUPC State
				/*-----------------------------------------------------------*/
				case INVALID:
					////invalid user input, i.e. non number characters,
				break;//End of INVALID state
				/*-----------------------------------------------------------*/
				case FIND:
				break;//End of FIND State
				/*-----------------------------------------------------------*/
				case FOUND:
				break;//End of FOUND State
				/*-----------------------------------------------------------*/
				case NOMATCH:
				break;//End of NOMATCH State
				/*-----------------------------------------------------------*/
				default:
				break;//End of Default
				}//End of StateStatus INV switch

			break;//End of INV State
			/*===============================================================*/
			default:
			break;//End of Default
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

