/*
 * LM35_PROGRAM.c
 *
 * Created: 10/25/2022 1:15:52 AM
 *  Author: AHMED ELDEEB
 */ 


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"

/* MCAL */
#include "DIO_interface.h"
#include "ADC_interface.h"
/* HAL */
#include "LM35_INTERFACE.h"

void LM35_Init(void)
{
	ADC_init();
}
u16 LM35_Read(void)
{

	u32 digitalValue;
	u32 analogValue,temp; 
	ADC_getDigitalValue(ADC_CHANNEL_1,&digitalValue);
	analogValue=(digitalValue * 500UL) / 1024;
	temp=analogValue;
	return temp;
}
