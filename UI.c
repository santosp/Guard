/*
 * UI.c
 *
 *  Created on: Jun 1, 2013
 *      Author: paul
 */
#include "Code_Standards.h"
#include "Ps2Keyboard.h"
#include "Graphics_Bmp.h"
#include "scancodes.h"

typedef enum{THR,OHR,TMIN,OMIN,TSEC,OSEC}TIMESET;
typedef enum{TM,OM,TD,OD,TY,OY}EXPSET;
INT8U ChartoDec[]={'0','1','2','3','4','5','6','7','8','9'};

void ReceiveTime(void){
	TIMESET timestate=THR;
	switch(timestate){
		case THR:
		break;
		case OHR:
		break;
		case TMIN:
		break;
		case OMIN:
		break;
		case TSEC:
		break;
		case OSEC:
		break;
	}

}
INT8U ReceiveExpDate(INT8U *buffer, INT8U count){
	static EXPSET expstate=TM;
	static INT8U lastkey=0;
	INT8U key=0;
	static INT8U bufcount;
	static INT8U backflag=FALSE;
	key=KeyPend(0);
	bufcount=count;
	switch(expstate){
		case TM:
			if(backflag){
				buffer[bufcount] = 0x00;
				backflag=0;
			}
			if(key>='0'&&key<='1'/*OR backspace*/){
				buffer[bufcount]=key;//add to buffer
				bufcount++;//increment buffer count
				//use look up table to find number
				//multiply number by 10
				//add it to months spot in temp time of day
				lastkey=key;
				expstate = OM;
			}else{/*Do Nothing*/}

		break;
		/*-----------------------------------------------------------*/
		case OM:
			if(backflag){
				buffer[bufcount] = 0x00;
				backflag=0;
			}
			if(lastkey=='1'){
				if(key>='0'&&key<='2'/*OR backspace*/){

					buffer[bufcount]=key;
					bufcount=bufcount+2;
					expstate = TD;

				}else {/*Do Nothing*/}
			}
			else if(key>='0'&&key<='9'/*OR backspace*/){
				buffer[bufcount]=key;//add to buffer
				bufcount=bufcount+2;//increment buffer count over '/'
				//use look up table to find number
				//add it to months spot in temp time of day
				expstate = TD;
			}
			else if(key==BS){
				backflag=1;
				bufcount--;
				expstate = TM;
			}else{/*Do Nothing*/}
		break;
		/*-----------------------------------------------------------*/
		//Input '/'
		/*-----------------------------------------------------------*/
		case TD:
			if(backflag){
				buffer[bufcount] = 0x00;
				backflag=0;
			}
			if(key>='0'&&key<='3'/*OR backspace*/){
				buffer[bufcount]=key;//add to buffer
				bufcount++;//increment buffer bufcount over '/'
				//use look up table to find number
				//add it to months spot in temp time of day
				expstate = OD;
			}
			else if(key==BS){
				backflag=1;
				bufcount=bufcount-2;;
				expstate = OM;
			}else{/*Do Nothing*/}
		break;
		/*-----------------------------------------------------------*/
		case OD:
			if(backflag){
				buffer[bufcount] = 0x00;
				backflag=0;
			}
			if(lastkey=='3'){
				if(key>='0'&&key<='1'/*OR backspace*/){

					buffer[bufcount]=key;
					bufcount=bufcount+2;
					expstate = TY;

				}else {/*Do Nothing*/}
			}
			else if(key>='0'&&key<='9'/*OR backspace*/){
				buffer[bufcount]=key;//add to buffer
				bufcount=bufcount+2;//increment buffer bufcount over '/'
				//use look up table to find number
				//add it to months spot in temp time of day
				expstate = TY;
			}
			else if(key==BS){
				backflag=1;
				bufcount--;
				expstate = OD;
			}else{/*Do Nothing*/}
		break;
		/*-----------------------------------------------------------*/
		//Input '/'
		/*-----------------------------------------------------------*/
		case TY:
			if(backflag){
				buffer[bufcount] = 0x00;
				backflag=0;
			}
			if(key>='1'&&key<='9'/*OR backspace*/){
				buffer[bufcount]=key;//add to buffer
				bufcount=+2;//increment buffer bufcount over '/'
				//use look up table to find number
				//add it to months spot in temp time of day
				expstate = OY;
			}
			else if(key==BS){
				backflag=1;
				bufcount=bufcount-2;
				expstate = OM;
			}else{/*Do Nothing*/}
		break;
		/*-----------------------------------------------------------*/
		case OY:
			if(lastkey=='1'){
				if(key>='3'&&key<='9'/*OR backspace*/){

					buffer[bufcount]=key;
					//bufcount=+2;
					//expstate = TD;

				}else {/*Do Nothing*/}
			}
			else if(key>='0'&&key<='9'/*OR backspace*/){
				buffer[bufcount]=key;//add to buffer
				//bufcount=+2;//increment buffer bufcount over '/'
				//use look up table to find number
				//add it to months spot in temp time of day
				//expstate = TY;
			}
			else if(key==BS){
				backflag=1;
				bufcount--;
				expstate = TY;
			}else{/*Do Nothing*/}
		break;
		/*-----------------------------------------------------------*/
		default:
		break;
	}
	draw_text_bmp(buffer,16,TPAGE5,MyFont,1);
	return bufcount;
}

