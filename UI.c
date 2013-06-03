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
typedef enum{TM,OM,TD,OD,TY,OY,CONT}EXPSET;
typedef enum{HUN,TEN,ONE,ENT}QUANTITY;
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
				bufcount++;//increment buffer bufcount over '/'
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
			if(backflag){
				buffer[bufcount] = 0x00;
				backflag=0;
			}
			if(lastkey=='1'){
				if(key>='3'&&key<='9'/*OR backspace*/){

					buffer[bufcount]=key;
					bufcount++;
					expstate = CONT;

				}else {/*Do Nothing*/}
			}
			else if(key>='0'&&key<='9'/*OR backspace*/){
				buffer[bufcount]=key;//add to buffer
				bufcount++;//increment buffer bufcount over '/'
				//use look up table to find number
				//add it to months spot in temp time of day
				expstate = CONT;
			}
			else if(key==BS){
				backflag=1;
				bufcount--;
				expstate = TY;
			}else{/*Do Nothing*/}
		break;
		/*-----------------------------------------------------------*/
		case CONT:
			if(key==0x0D){
				bufcount++;
				expstate = TM;
			}
			else if(key==BS){
				backflag=1;
				bufcount--;
				expstate = TY;
			}else{/*Do Nothing*/}
			key=0;
		break;
		/*-----------------------------------------------------------*/
		default:
		break;
	}
	draw_text_bmp(buffer,16,TPAGE5,MyFont,1);
	return bufcount;
}
INT8U ReceiveQuan(INT8U *buffer, INT8U count){
	static QUANTITY quanstate=HUN;
	static INT8U backflag=FALSE;
	static INT8U lastkey=0;
	INT8U key=0;
	INT8U bufcount=0;
	bufcount=count;
	key=KeyPend(0);
	switch(quanstate){
		case HUN:
			if(backflag){
				buffer[bufcount] = 0x00;
				backflag=0;
			}
			if(key>='0'&&key<='2'){
				buffer[bufcount]=key;
				bufcount++;
				quanstate = TEN;
			}else{/*Do Nothing*/}
		break;
		case TEN:
			if(backflag){
				buffer[bufcount] = 0x00;
				backflag=0;
			}
			if(lastkey=='2'){
				if(key>='0'&&key<='5'/*OR backspace*/){

					buffer[bufcount]=key;
					bufcount++;
					quanstate = ONE;

				}else {/*Do Nothing*/}
			}
			else if(key>='0'&&key<='9'/*OR backspace*/){
				buffer[bufcount]=key;//add to buffer
				bufcount++;//increment buffer bufcount over '/'
				//use look up table to find number
				//add it to months spot in temp time of day
				quanstate = ONE;
			}
			else if(key==BS){
				backflag=1;
				bufcount--;
				quanstate = HUN;
			}else{/*Do Nothing*/}
		break;
		case ONE:
			if(backflag){
				buffer[bufcount] = 0x00;
				backflag=0;
			}
			if(key>='0'&&key<='9'/*OR backspace*/){
				buffer[bufcount]=key;//add to buffer
				bufcount++;//increment buffer bufcount over '/'
				//use look up table to find number
				//add it to months spot in temp time of day
				quanstate = ENT;
			}
			else if(key==BS){
				backflag=1;
				bufcount--;
				quanstate = TEN;
			}else{/*Do Nothing*/}
		break;
		case ENT:

			if(key==CR){
				bufcount++;
				quanstate = HUN;
			}
			else if(key==BS){
				backflag=1;
				bufcount--;
				quanstate = ONE;
			}else{/*Do Nothing*/}
			key=0;

		break;
		default:
		break;
	}
	lastkey=key;
	draw_text_bmp(buffer,16,TPAGE5,MyFont,1);
	return bufcount;
}

INT16U StringtoDec(INT8U* string){
	INT16U valcount=0,temp=0;

	for(valcount=0;string[valcount]!=0x00;valcount++){
		temp=(10*temp)+(string[valcount]-'0');
	}
return temp;
}

void ClearString(INT8U* string){
	INT8U temp=0;
	for(temp=0;string[temp]!=0x00;temp++){
		string[temp]=0x00;
	}

}
