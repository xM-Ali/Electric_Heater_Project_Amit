/*
 * SSD_PROGRAM.c
 *
 * Created: 10/25/2022 1:27:57 AM
 *  Author: AHMED ELDEEB
 */ 


#define F_CPU   16000000UL
#include <util/delay.h>

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"

/* MCAL */
#include "DIO_INTERFACE.h"

/* HAL */
#include "SSD_INTERFACE.h"

void SSD_Init(void)
{
	DIO_setPinDirection(DIO_PORTB,DIO_PIN3,DIO_PIN_OUTPUT);//EN
	DIO_setPinDirection(DIO_PORTA,DIO_PIN4,DIO_PIN_OUTPUT);//A PIN
	DIO_setPinDirection(DIO_PORTA,DIO_PIN5,DIO_PIN_OUTPUT);//B PIN
	DIO_setPinDirection(DIO_PORTA,DIO_PIN6,DIO_PIN_OUTPUT);//C PIN
	DIO_setPinDirection(DIO_PORTA,DIO_PIN7,DIO_PIN_OUTPUT);//D PIN
	DIO_setPinDirection(DIO_PORTB,DIO_PIN4,DIO_PIN_OUTPUT);//E PIN
	DIO_setPinDirection(DIO_PORTB,DIO_PIN5,DIO_PIN_OUTPUT);//F PIN
	DIO_setPinDirection(DIO_PORTB,DIO_PIN6,DIO_PIN_OUTPUT);//G PIN
	DIO_setPinDirection(DIO_PORTB,DIO_PIN7,DIO_PIN_OUTPUT);//H PIN
	DIO_setPinValue(DIO_PORTB,DIO_PIN3,DIO_PIN_LOW);//EN LOW
}

void SSD_BLINK(void)
{
	DIO_setPinValue(DIO_PORTB,DIO_PIN3,DIO_PIN_HIGH);
	_delay_ms(200);
	DIO_setPinValue(DIO_PORTB,DIO_PIN3,DIO_PIN_LOW);
}

void SSD_WriteNumber(u16 number)
{
		u8 Units = number % 10;
		u8 Tens = number / 10;
		SSD_DigitDisplayTens(Tens);
		SSD_DigitDisplayUnits(Units);	
}

static void SSD_DigitDisplayTens(u8 number) {
	switch (number) 
	{
		case 0:
		DIO_setPinValue(DIO_PORTA,DIO_PIN4,DIO_PIN_LOW);
		DIO_setPinValue(DIO_PORTA,DIO_PIN5,DIO_PIN_LOW);
		DIO_setPinValue(DIO_PORTA,DIO_PIN6,DIO_PIN_LOW);
		DIO_setPinValue(DIO_PORTA,DIO_PIN7,DIO_PIN_LOW);
		break;
		
		case 1:
		DIO_setPinValue(DIO_PORTA,DIO_PIN4,DIO_PIN_HIGH);
		DIO_setPinValue(DIO_PORTA,DIO_PIN5,DIO_PIN_LOW);
		DIO_setPinValue(DIO_PORTA,DIO_PIN6,DIO_PIN_LOW);
		DIO_setPinValue(DIO_PORTA,DIO_PIN7,DIO_PIN_LOW);
		break;
		
		case 2:
		DIO_setPinValue(DIO_PORTA,DIO_PIN4,DIO_PIN_LOW);
		DIO_setPinValue(DIO_PORTA,DIO_PIN5,DIO_PIN_HIGH);
		DIO_setPinValue(DIO_PORTA,DIO_PIN6,DIO_PIN_LOW);
		DIO_setPinValue(DIO_PORTA,DIO_PIN7,DIO_PIN_LOW);
		break;
		
		case 3:
		DIO_setPinValue(DIO_PORTA,DIO_PIN4,DIO_PIN_HIGH);
		DIO_setPinValue(DIO_PORTA,DIO_PIN5,DIO_PIN_HIGH);
		DIO_setPinValue(DIO_PORTA,DIO_PIN6,DIO_PIN_LOW);
		DIO_setPinValue(DIO_PORTA,DIO_PIN7,DIO_PIN_LOW);
		break;
		
		case 4:
		DIO_setPinValue(DIO_PORTA,DIO_PIN4,DIO_PIN_LOW);
		DIO_setPinValue(DIO_PORTA,DIO_PIN5,DIO_PIN_LOW);
		DIO_setPinValue(DIO_PORTA,DIO_PIN6,DIO_PIN_HIGH);
		DIO_setPinValue(DIO_PORTA,DIO_PIN7,DIO_PIN_LOW);
		break;
		
		case 5:
		DIO_setPinValue(DIO_PORTA,DIO_PIN4,DIO_PIN_HIGH);
		DIO_setPinValue(DIO_PORTA,DIO_PIN5,DIO_PIN_LOW);
		DIO_setPinValue(DIO_PORTA,DIO_PIN6,DIO_PIN_HIGH);
		DIO_setPinValue(DIO_PORTA,DIO_PIN7,DIO_PIN_LOW);
		break;
		
		case 6:
		DIO_setPinValue(DIO_PORTA,DIO_PIN4,DIO_PIN_LOW);
		DIO_setPinValue(DIO_PORTA,DIO_PIN5,DIO_PIN_HIGH);
		DIO_setPinValue(DIO_PORTA,DIO_PIN6,DIO_PIN_HIGH);
		DIO_setPinValue(DIO_PORTA,DIO_PIN7,DIO_PIN_LOW);
		break;
		
		case 7:
		DIO_setPinValue(DIO_PORTA,DIO_PIN4,DIO_PIN_HIGH);
		DIO_setPinValue(DIO_PORTA,DIO_PIN5,DIO_PIN_HIGH);
		DIO_setPinValue(DIO_PORTA,DIO_PIN6,DIO_PIN_HIGH);
		DIO_setPinValue(DIO_PORTA,DIO_PIN7,DIO_PIN_LOW);
		break;
		
		case 8:
		DIO_setPinValue(DIO_PORTA,DIO_PIN4,DIO_PIN_LOW);
		DIO_setPinValue(DIO_PORTA,DIO_PIN5,DIO_PIN_LOW);
		DIO_setPinValue(DIO_PORTA,DIO_PIN6,DIO_PIN_LOW);
		DIO_setPinValue(DIO_PORTA,DIO_PIN7,DIO_PIN_HIGH);
		break;
		
		case 9:
		DIO_setPinValue(DIO_PORTA,DIO_PIN4,DIO_PIN_HIGH);
		DIO_setPinValue(DIO_PORTA,DIO_PIN5,DIO_PIN_LOW);
		DIO_setPinValue(DIO_PORTA,DIO_PIN6,DIO_PIN_LOW);
		DIO_setPinValue(DIO_PORTA,DIO_PIN7,DIO_PIN_HIGH);
		break;
		
		default:
		break;
	}
}

static void SSD_DigitDisplayUnits(u8 number) {
	switch (number)
	{
		case 0:
		DIO_setPinValue(DIO_PORTB,DIO_PIN4,DIO_PIN_LOW);
		DIO_setPinValue(DIO_PORTB,DIO_PIN5,DIO_PIN_LOW);
		DIO_setPinValue(DIO_PORTB,DIO_PIN6,DIO_PIN_LOW);
		DIO_setPinValue(DIO_PORTB,DIO_PIN7,DIO_PIN_LOW);
		break;
		
		case 1:
		DIO_setPinValue(DIO_PORTB,DIO_PIN4,DIO_PIN_HIGH);
		DIO_setPinValue(DIO_PORTB,DIO_PIN5,DIO_PIN_LOW);
		DIO_setPinValue(DIO_PORTB,DIO_PIN6,DIO_PIN_LOW);
		DIO_setPinValue(DIO_PORTB,DIO_PIN7,DIO_PIN_LOW);
		break;
		
		case 2:
		DIO_setPinValue(DIO_PORTB,DIO_PIN4,DIO_PIN_LOW);
		DIO_setPinValue(DIO_PORTB,DIO_PIN5,DIO_PIN_HIGH);
		DIO_setPinValue(DIO_PORTB,DIO_PIN6,DIO_PIN_LOW);
		DIO_setPinValue(DIO_PORTB,DIO_PIN7,DIO_PIN_LOW);
		break;
		
		case 3:
		DIO_setPinValue(DIO_PORTB,DIO_PIN4,DIO_PIN_HIGH);
		DIO_setPinValue(DIO_PORTB,DIO_PIN5,DIO_PIN_HIGH);
		DIO_setPinValue(DIO_PORTB,DIO_PIN6,DIO_PIN_LOW);
		DIO_setPinValue(DIO_PORTB,DIO_PIN7,DIO_PIN_LOW);
		break;
		
		case 4:
		DIO_setPinValue(DIO_PORTB,DIO_PIN4,DIO_PIN_LOW);
		DIO_setPinValue(DIO_PORTB,DIO_PIN5,DIO_PIN_LOW);
		DIO_setPinValue(DIO_PORTB,DIO_PIN6,DIO_PIN_HIGH);
		DIO_setPinValue(DIO_PORTB,DIO_PIN7,DIO_PIN_LOW);
		break;
		
		case 5:
		DIO_setPinValue(DIO_PORTB,DIO_PIN4,DIO_PIN_HIGH);
		DIO_setPinValue(DIO_PORTB,DIO_PIN5,DIO_PIN_LOW);
		DIO_setPinValue(DIO_PORTB,DIO_PIN6,DIO_PIN_HIGH);
		DIO_setPinValue(DIO_PORTB,DIO_PIN7,DIO_PIN_LOW);
		break;
		
		case 6:
		DIO_setPinValue(DIO_PORTB,DIO_PIN4,DIO_PIN_LOW);
		DIO_setPinValue(DIO_PORTB,DIO_PIN5,DIO_PIN_HIGH);
		DIO_setPinValue(DIO_PORTB,DIO_PIN6,DIO_PIN_HIGH);
		DIO_setPinValue(DIO_PORTB,DIO_PIN7,DIO_PIN_LOW);
		break;
		
		case 7:
		DIO_setPinValue(DIO_PORTB,DIO_PIN4,DIO_PIN_HIGH);
		DIO_setPinValue(DIO_PORTB,DIO_PIN5,DIO_PIN_HIGH);
		DIO_setPinValue(DIO_PORTB,DIO_PIN6,DIO_PIN_HIGH);
		DIO_setPinValue(DIO_PORTB,DIO_PIN7,DIO_PIN_LOW);
		break;
		
		case 8:
		DIO_setPinValue(DIO_PORTB,DIO_PIN4,DIO_PIN_LOW);
		DIO_setPinValue(DIO_PORTB,DIO_PIN5,DIO_PIN_LOW);
		DIO_setPinValue(DIO_PORTB,DIO_PIN6,DIO_PIN_LOW);
		DIO_setPinValue(DIO_PORTB,DIO_PIN7,DIO_PIN_HIGH);
		break;
		
		case 9:
		DIO_setPinValue(DIO_PORTB,DIO_PIN4,DIO_PIN_HIGH);
		DIO_setPinValue(DIO_PORTB,DIO_PIN5,DIO_PIN_LOW);
		DIO_setPinValue(DIO_PORTB,DIO_PIN6,DIO_PIN_LOW);
		DIO_setPinValue(DIO_PORTB,DIO_PIN7,DIO_PIN_HIGH);
		break;
		
		default:
		break;
		
	}
}