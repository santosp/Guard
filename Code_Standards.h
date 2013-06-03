/*
 * Code_Standards.h
 *
 *  Created on: Mar 30, 2013
 *      Author: Paul Santos
 */

#ifndef CODE_STANDARDS_H_
#define CODE_STANDARDS_H_
/*	Type Defines  */
typedef unsigned char   INT8U;
typedef signed char     INT8S;
typedef unsigned short  INT16U;
typedef signed short    INT16S;
typedef unsigned long   INT32U;
typedef signed long     INT32S;

typedef enum {WELCOME,MAIN,ADD,REMOVE,INV}UISTATE;
typedef enum {INIT,GETUPC,INVALID,FIND,FOUND,EXP,QUAN,NOMATCH}SUBSTATE;
//typedef enum {INIT,INVALID}WELCOMESUBSTATE;

typedef struct{
	UISTATE UserState;
	SUBSTATE StateStatus;
	INT8U	WaitforKey;
}UISTATEINFO;

typedef struct{
	INT8U Discription[16];
	INT8U Experation[8];
	INT8U Timestamp[8];
	INT8U UPC[11];
	INT8U Quantity;
}ITEMINFO;

typedef struct{
	INT8U ArrowCount;
	INT8U PageCount;
	INT8U LastPage;
	INT8U ItemCount;
	INT8U LastArrow;
}INVINFO;

/* Constant Defines */

#define MAXUPC 11
#define WAIT10 10

/*	Boolean Defines  */
#define TRUE 1
#define FALSE 0
/*	Macro Definitions  */
#define BIT_SET(Location,Mask) GPIOPinWrite(Location, Mask, Mask)//((Location) |= (Mask))
#define BIT_CLR(Location,Mask) GPIOPinWrite(Location, Mask, 0x00)//((Location) &= ~(Mask))

/*

*/
#endif /* CODE_STANDARDS_H_ */
