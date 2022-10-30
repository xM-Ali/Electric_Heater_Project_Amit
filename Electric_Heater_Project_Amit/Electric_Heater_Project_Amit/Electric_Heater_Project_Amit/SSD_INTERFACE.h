/*
 * SSD_INTERFACE.h
 *
 * Created: 10/25/2022 1:28:19 AM
 *  Author: AHMED ELDEEB
 */ 


#ifndef SSD_INTERFACE_H_
#define SSD_INTERFACE_H_

void SSD_Init(void);
void SSD_WriteNumber(u16 number);
void SSD_BLINK(void);
static void SSD_DigitDisplayTens(u8 number);
static void SSD_DigitDisplayUnits(u8 number);

#endif /* SSD_INTERFACE_H_ */