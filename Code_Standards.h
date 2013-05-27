/*
 * Code_Standards.h
 *
 *  Created on: Mar 30, 2013
 *      Author: Alix
 */

#ifndef CODE_STANDARDS_H_
#define CODE_STANDARDS_H_

typedef unsigned char   INT8U;
typedef signed char     INT8S;
typedef unsigned short  INT16U;
typedef signed short    INT16S;
typedef unsigned long   INT32U;
typedef signed long     INT32S;

typedef enum {WELCOME,MAIN,ADD,REMOVE,INV}UISTATE;
typedef struct{
	UISTATE UserState;
	INT8U StateInit;
}UISTATEINFO;

#define TRUE 1
#define FALSE 0

#define BIT_SET(Location,Mask) GPIOPinWrite(Location, Mask, Mask)//((Location) |= (Mask))
#define BIT_CLR(Location,Mask) GPIOPinWrite(Location, Mask, 0x00)//((Location) &= ~(Mask))

/*
//Function Prototypes
void int_to_string(INT16U x, INT8U *string);
void string_rev(INT8U *string);
void String_Copy(INT8U *g_string, INT8U *t_string,INT8U c);
*/
#endif /* CODE_STANDARDS_H_ */
