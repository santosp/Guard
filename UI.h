/*
 * UI.h
 *
 *  Created on: Jun 1, 2013
 *      Author: paul
 */

#ifndef UI_H_
#define UI_H_

extern INT8U ReceiveExpDate(INT8U *buffer, INT8U count);
extern INT8U ReceiveQuan(INT8U *buffer, INT8U count);
extern INT16U StringtoDec(INT8U* string);
extern void ClearString(INT8U* string);

#endif /* UI_H_ */
