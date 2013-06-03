/*
 *  ======== main.c ========
 */

#include <xdc/std.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>

#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/gates/GateMutexPri.h>






#include "Graphics_Bmp.h"
#include "Font.h"
#include "st7565.h"
#include "Code_Standards.h"
#include "Clock.h"
#include "Ps2Keyboard.h"

#include "UiMessages.h"
#include "UI.h"
#include "Items.h"
/*=======*/
//Globals
UISTATEINFO StateInfo={ADD,INIT,FALSE}; // NEED TO START IN WELCOME not Remove
UISTATE LastState=MAIN;
INVINFO InvInfo={0,0,0,0,0};

extern INT8U ItemLookUp[][2];
extern ITEMINFO ItemBlock1[25];

/*=======*/
const INT8U PageLookup[]={TPAGE1,TPAGE2,TPAGE3,TPAGE4,TPAGE5};

/*
 *  ======== taskFxn ========
 */
Void UiTask(UArg a0, UArg a1)
{
	INT8U key=0;
	INT8U timedatebuffer[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	INT8U upcbuffer[12]={0,0,0,0,0,0,0,0,0,0,0,0};
	INT8U expbuffer[]={0,0,'/',0,0,'/',0,0,0};
	INT8U quanbuffer[]={0,0,0,0};

	INT8U upccount=0,inputcount=0,itemfound=0,lookupcount=0,upc_count=0;
	INT8U clearcount=0;
	INT8U passflag=0;
	INT8U expcount=0;
	INT8U quancount=0;
	INT8U count=0;
	INT8U testcount=0;
	while(1){
		switch(StateInfo.UserState){
			case WELCOME:
				switch (StateInfo.StateStatus){
				case INIT:
					WelcomeMsg();
					StateInfo.StateStatus = GETUPC;
				break;//End of INIT State
				/*-----------------------------------------------------------*/
				case GETUPC:
					key=KeyPend(0);
					if(upccount<6){
						if(key>='0' && key<='9'){
							timedatebuffer[upccount]=key;
							upccount++;
							if(upccount==2){
								//input a : and add to symbol count
								timedatebuffer[upccount]=':';
								upccount++;
							}
							else if(upccount==5){
								//input a , and add to symbol count
								timedatebuffer[upccount]=',';
								upccount++;
							}else{/*Do nothing*/}
							//draw_text_bmp(upcbuffer,16,PAGE6,MyFont,1);
						}else{/*Do nothing*/}
					}
					else if(upccount>=6&&upccount<=13){
						if(key>='0' && key<='9'){
							timedatebuffer[upccount]=key;
							upccount++;
							if(upccount==8||upccount==11){
								//input a : and add to symbol count
								timedatebuffer[upccount]='/';
								upccount++;
							}else{/*Do nothing*/}
							//draw_text_bmp(upcbuffer,16,PAGE6,MyFont,1);
						}else{/*Do nothing*/}
					}else if(upccount==14){
						StateInfo.StateStatus = INIT;
						StateInfo.UserState = MAIN;
					}else{/*Do nothing*/}
					draw_text_bmp(timedatebuffer,16,PAGE6,MyFont,1);
					key=0;
				break;//End of GETUPC State

				case INVALID:
				case FIND:
				case FOUND:
				case NOMATCH:
				default:
					/* Do Nothing*/
				break;//End of Default
				}//End of StateStatus WELCOME switch

			break;
			/*===============================================================*/
			case MAIN:
				switch (StateInfo.StateStatus){
				case INIT:
					MainMsg();
					StateInfo.StateStatus = GETUPC;
				break;//End of INIT State
				/*-----------------------------------------------------------*/
				case GETUPC:
					/* Do Nothing untill button press*/
				break;//End of GETUPC State
				/*-----------------------------------------------------------*/
				case INVALID:
				case FIND:
				case FOUND:
				case NOMATCH:
				default:
					/* Do Nothing*/
				break;//End of Default
				}//End of StateStatus MAIN switch

			break;//END of MAIN State
			/*===============================================================*/
			case ADD:
				switch (StateInfo.StateStatus){
				case INIT:

					AddMsg();

					for(clearcount=0;clearcount<MAXUPC;clearcount++){// clear buffer
						upcbuffer[clearcount]=0;
					}
					//ClearString(quanbuffer);
					upccount=0;
					itemfound=0;
					StateInfo.StateStatus = GETUPC;
					StateInfo.WaitforKey = FALSE;
				break;//End of INIT State
				/*-----------------------------------------------------------*/
				case GETUPC:
					key=KeyPend(0);
					if(key>='0' && key<='9'){
						upcbuffer[upccount]=key;
						upccount++;
						draw_text_bmp(upcbuffer,16,TPAGE5,MyFont,1);
					}else if(key==0x08){
						upccount--;
						upcbuffer[upccount]=' ';
						draw_text_bmp(upcbuffer,16,TPAGE5,MyFont,1);
					}
					key=0;
					//Continues to look for UPC if there was a valid all number entry
					if(upccount>10){
						upccount=0;
						// Will exit loop if input is not a number or when all the characters have been read
						for(inputcount=0;(upcbuffer[inputcount]<='9'&&upcbuffer[inputcount]>='0')&&inputcount<MAXUPC;inputcount++);
						//If
						if(inputcount>10){
							//valid input
							StateInfo.StateStatus=FIND;
						}
						else{
							//invalid input, i.e. non number characters
							StateInfo.StateStatus=INVALID;
							draw_text_bmp((INT8U *)"INVALID ",16,PAGE3,MyFont,1);
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
							for(upc_count=0;upcbuffer[upc_count]==ItemBlock1[lookupcount].UPC[upc_count]&&upc_count<MAXUPC;upc_count++);
							if(upc_count<MAXUPC){
								//No match
								//Give user option to either re enter or add to inventory
								StateInfo.StateStatus = NOMATCH;
								//draw_text_bmp((INT8U *)"NO Match ",16,24,MyFont,1);
							}
							else{
								//found item
								itemfound=1;
								StateInfo.StateStatus = FOUND;
								//draw_text_bmp((INT8U *)"FOUND ",16,PAGE3,MyFont,1);
							}
						}
						else{
							//No item of this UPC number
							//Give user option to either re enter or add to inventory
							StateInfo.StateStatus = NOMATCH;
							//draw_text_bmp((INT8U *)"NO Match ",16,PAGE3,MyFont,1);
						}
					}
				break;//End of Find
				/*-----------------------------------------------------------*/
				case FOUND:
					AddMsgFound();
					draw_text_bmp((INT8U *)ItemBlock1[lookupcount-1].Discription,30,TPAGE1,MyFont,1);
					StateInfo.StateStatus = EXP;
				break;//End of FOUND
				/*-----------------------------------------------------------*/
				case EXP:
					if(!passflag){
						expcount=ReceiveExpDate(expbuffer,expcount);
						if(expcount>=9){
							passflag=TRUE;
						}
						else{}
					}
					else{
						//add to items expdate
						count=expcount;
						for(count=0;count<=expcount;count++){
							ItemBlock1[lookupcount-1].Experation[count]=expbuffer[count];
						}

						StateInfo.StateStatus = QUAN;
						passflag=FALSE;
						AddMsgQuan();
						count=0;
						expcount=0;
					}
				break;//End of FOUND
				/*-----------------------------------------------------------*/
				case QUAN:
					if(!passflag){

						count=ReceiveQuan(quanbuffer,count);
						if(count>=4){
							passflag=TRUE;
						}
					}
					else{
						//function to turn string to int
					quancount=(INT8U) StringtoDec(quanbuffer);
					ItemBlock1[lookupcount-1].Quantity=+quancount;
					ItemLookUp[lookupcount-1][0]=ItemBlock1[lookupcount-1].Quantity;
					StateInfo.StateStatus = INIT;
					passflag=FALSE;
					}
				break;//End of FOUND
				/*-----------------------------------------------------------*/
				case NOMATCH:
					if(!StateInfo.WaitforKey){
						AddMsgNoMatch();
						//draw_text_bmp((INT8U *)"No Match, Would you like to add UPC?Y/N?",16,PAGE7,MyFont,1);
						StateInfo.WaitforKey=TRUE;
					}
					else{
						//Loop until a function key is pressed
					}
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
					RemoveMsg();
					//draw_text_bmp((INT8U *)"REMOVE STATE ",16,PAGE5,MyFont,1);

					//draw_text_bmp((INT8U *)"         ",16,PAGE3,MyFont,1);// clear found or not space
					//draw_text_bmp((INT8U *)"             ",16,PAGE6,MyFont,1);//clear upcbuffer space
					for(clearcount=0;clearcount<11;clearcount++){// clear buffer
						upcbuffer[clearcount]=0;
					}
					upccount=0;
					itemfound=0;
					StateInfo.StateStatus = GETUPC;
				break;//End of INIT State
				/*-----------------------------------------------------------*/
				case GETUPC:
					key=KeyPend(0);
					if(key>='0' && key<='9'){
						upcbuffer[upccount]=key;
						upccount++;
						draw_text_bmp(upcbuffer,16,TPAGE5,MyFont,1);
					}
					key=0;
					if(upccount>10){
						upccount=0;
						// Will exit loop if input is not a number or when all the characters have been read
						for(inputcount=0;(upcbuffer[inputcount]<='9'&&upcbuffer[inputcount]>='0')&&inputcount<11;inputcount++);
						//Continues to look for UPC if there was a valid all number entry
						if(inputcount>10){
							//valid input
							StateInfo.StateStatus=FIND;
						}
						else{
							//invalid input, i.e. non number characters
							StateInfo.StateStatus=INVALID;
							draw_text_bmp((INT8U *)"INVALID ",16,PAGE3,MyFont,1);
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
								//draw_text_bmp((INT8U *)"FOUND ",16,PAGE3,MyFont,1);
							}
						}
						else{
							//No item of this UPC number
							//Give user option to either re enter or add to inventory
							StateInfo.StateStatus = NOMATCH;
							//draw_text_bmp((INT8U *)"NO Match ",16,PAGE3,MyFont,1);
						}
					}
				break;//End of FIND State
				/*-----------------------------------------------------------*/
				case FOUND:
					ItemBlock1[lookupcount-1].Quantity--;
					ItemLookUp[lookupcount-1][0]=ItemBlock1[lookupcount-1].Quantity;
					StateInfo.StateStatus = INIT;
				break;//End of FOUND State
				/*-----------------------------------------------------------*/
				case NOMATCH:
					draw_text_bmp((INT8U *)"No Match, Please Try again",16,PAGE7,MyFont,1);
					StateInfo.WaitforKey=TRUE;
					//flush buffer and buffer space and counters
					StateInfo.StateStatus = GETUPC;
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
					InvMsg();
					StateInfo.StateStatus = INVALID;
					//draw_text_bmp((INT8U *)"INV STATE ",16,PAGE5,MyFont,1);
				break;//End of INIT State
				/*-----------------------------------------------------------*/
				case GETUPC:
					if(InvInfo.PageCount>InvInfo.LastPage){
						glcd_blank_page(LPAGE1);
						glcd_blank_page(LPAGE2);
						glcd_blank_page(LPAGE3);
						glcd_blank_page(LPAGE4);
						glcd_blank_page(LPAGE5);
						if(InvInfo.ItemCount<4){//Possibly Don't Need This conditional
							for(count=testcount;(count<25)&&(InvInfo.ItemCount<5);count++){
								if(ItemLookUp[count][0]>0){
									draw_text_bmp((ItemBlock1[count].Discription),10,PageLookup[InvInfo.ItemCount],MyFont,1);
									draw_text_bmp(ItemBlock1[count].Experation,75,PageLookup[InvInfo.ItemCount],MyFont,1);
									draw_text_bmp((INT8U *)"->",1,PageLookup[InvInfo.ArrowCount],MyFont,1);
									InvInfo.ItemCount++;
									testcount=count;
								}else{/*Do Nothing*/}
							}
						}else{/*Do Nothing*/}
					}
					else if(InvInfo.PageCount<InvInfo.LastPage){
						glcd_blank_page(LPAGE1);
						glcd_blank_page(LPAGE2);
						glcd_blank_page(LPAGE3);
						glcd_blank_page(LPAGE4);
						glcd_blank_page(LPAGE5);
						if(InvInfo.ItemCount<4){//Possibly Don't Need This conditional
							for(count;(count>0)&&(InvInfo.ItemCount<5);count--){
								if(ItemLookUp[count][0]>0){
									draw_text_bmp(ItemBlock1[count].Discription,10,PageLookup[InvInfo.ItemCount],MyFont,1);
									draw_text_bmp(ItemBlock1[count].Experation,75,PageLookup[InvInfo.ItemCount],MyFont,1);
									draw_text_bmp((INT8U *)"->",1,PageLookup[InvInfo.ArrowCount],MyFont,1);
									InvInfo.ItemCount++;
									testcount=count;
								}else{/*Do Nothing*/}
							}
						}else{/*Do Nothing*/}
					}
					else{
						//InvInfo.ItemCount=0;

					}
					if(InvInfo.LastArrow!=InvInfo.ArrowCount){
						//glcd_blank_pagexy(PageLookup[InvInfo.LastArrow],1,8);
						draw_text_bmp((INT8U *)"  ",1,PageLookup[InvInfo.LastArrow],MyFont,1);
						draw_text_bmp((INT8U *)"->",1,PageLookup[InvInfo.ArrowCount],MyFont,1);
					}
				break;//End of GETUPC State
				/*-----------------------------------------------------------*/
				case INVALID:
					if(InvInfo.ItemCount<4){//Possibly Don't Need This conditional
						for(count=0;(count<25)&&(InvInfo.ItemCount<5);count++){
							if(ItemLookUp[count][0]>0){
								draw_text_bmp((ItemBlock1[count].Discription),10,PageLookup[InvInfo.ItemCount],MyFont,1);
								draw_text_bmp(ItemBlock1[count].Experation,75,PageLookup[InvInfo.ItemCount],MyFont,1);
								draw_text_bmp((INT8U *)"->",1,PageLookup[InvInfo.ArrowCount],MyFont,1);
								InvInfo.ItemCount++;
								testcount=count;
							}else{/*Do Nothing*/}
						}
					}else{
						StateInfo.StateStatus = GETUPC;
						//testcount--;
					}
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

    glcd_init();
    glcd_command(GLCD_CMD_DISPLAY_ON);
	glcd_blank();
	KeyboardInit();
    BIOS_start();        /* enable interrupts and start SYS/BIOS */
}

