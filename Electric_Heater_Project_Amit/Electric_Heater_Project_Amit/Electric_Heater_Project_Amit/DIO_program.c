/*
 * DIO_program.c
 *
 * Created: 9/6/2022 11:32:39 AM
 *  Author: AMIT
 */ 

 /* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"

/* MCAL */
#include "DIO_interface.h"


/* Pin Apis */								   
void DIO_setPinDirection(u8 PortId, u8 PinId, u8 PinDirection)
{
	if((PortId<=3) && (PinId<=7) && ((PinDirection == DIO_PIN_OUTPUT) || 
   (PinDirection == DIO_PIN_INPUT)))
   {
	   switch(PortId)
	{
		case 0 :
		if(DIO_PIN_OUTPUT == PinDirection)
		{
			SET_BIT(DDRA, PinId);
		}
		else 
		{
			CLR_BIT(DDRA, PinId);
		}
		break;
		
		case 1 :
		if(DIO_PIN_OUTPUT == PinDirection)
		{
			SET_BIT(DDRB, PinId);
		}
		else 
		{
			CLR_BIT(DDRB, PinId);
		}
		break;
		
		case 2 :
		if(DIO_PIN_OUTPUT == PinDirection)
		{
			SET_BIT(DDRC, PinId);
		}
		else 
		{
			CLR_BIT(DDRC, PinId);
		}
		break;
		
		case 3 :
		if(DIO_PIN_OUTPUT == PinDirection)
		{
			SET_BIT(DDRD, PinId);
		}
		else 
		{
			CLR_BIT(DDRD, PinId);
		}
		break;
	} 
   }
}


void DIO_setPinValue(u8 PortId, u8 PinId, u8 PinValue)
{
	if((PortId<=3) && (PinId<=7) && ((PinValue == DIO_PIN_HIGH) || (PinValue == DIO_PIN_LOW)))
	{
		switch(PortId)
		{
			case 0: //DIO_PORTA
			if (DIO_PIN_HIGH == PinValue)
			{
				SET_BIT(PORTA,PinId);
			}
			else
			{
				CLR_BIT(PORTA,PinId);
			}
			break;
			
			case 1: //DIO_PORTB
			if (DIO_PIN_HIGH == PinValue)
			{
				SET_BIT(PORTB,PinId);
			}
			else
			{
				CLR_BIT(PORTB,PinId);
			}
			break;
			
			case 2: //DIO_PORTC
			if (DIO_PIN_HIGH == PinValue)
			{
				SET_BIT(PORTC,PinId);
			}
			else
			{
				CLR_BIT(PORTC,PinId);
			}
			break;
			
			case 3: //DIO_PORTD
			if (DIO_PIN_HIGH == PinValue)
			{
				SET_BIT(PORTD,PinId);
			}
			else
			{
				CLR_BIT(PORTD,PinId);
			}
			break;
		}
	}
}


void DIO_getPinValue(u8 PortId, u8 PinId, u8* PinValue)
{
	if((PortId<=3) && (PinId<=7) && (PinValue != NULL))
	{
		switch(PortId)
		{
			case 0: //DIO_PORTA
			if(DIO_PIN_HIGH == GET_BIT(PINA,PinId))
			{
				*PinValue = DIO_PIN_HIGH;
			}
			else
			{
				*PinValue = DIO_PIN_LOW;
			}
			break;
			
			case 1: //DIO_PORTB
			if(DIO_PIN_HIGH == GET_BIT(PINB,PinId))
			{
				*PinValue = DIO_PIN_HIGH;
			}
			else
			{
				*PinValue = DIO_PIN_LOW;
			}
			break;
			
			case 2: //DIO_PORTC
			if(DIO_PIN_HIGH == GET_BIT(PINC,PinId))
			{
				*PinValue = DIO_PIN_HIGH;
			}
			else
			{
				*PinValue = DIO_PIN_LOW;
			}
			break;
			
			case 3: //DIO_PORTD
			if(DIO_PIN_HIGH == GET_BIT(PIND,PinId))
			{
				*PinValue = DIO_PIN_HIGH;
			}
			else
			{
				*PinValue = DIO_PIN_LOW;
			}
			break;
		}
	}
}


void DIO_togglePinValue(u8 PortId, u8 PinId)
{
	if((PortId<=3) && (PinId<=7))
	{
		switch(PortId)
		{
			case 0: //DIO_PORTA
			TOG_BIT(PORTA,PinId);
			break;
			
			case 1: //DIO_PORTB
			TOG_BIT(PORTB,PinId);
			break;
			
			case 2: //DIO_PORTC
			TOG_BIT(PORTC,PinId);
			break;
			
			case 3: //DIO_PORTD
			TOG_BIT(PORTD,PinId);
			break;
		}
	}
}


void DIO_setInputPinResistance(u8 PortId, u8 PinId)
{
	if((PortId<=3) && (PinId<=7))
	{
		switch(PortId)
		{
			case 0:
			SET_BIT(PORTA,PinId);
			break;
			
			case 1:
			SET_BIT(PORTB,PinId);
			break;
			
			case 2:
			SET_BIT(PORTC,PinId);
			break;
			
			case 3:
			SET_BIT(PORTD,PinId);
			break;
		}
	}
}


/* Port Apis */	
void DIO_setPortDirection(u8 PortId, u8 PortDirection)
{
	if((PortId<=3) && ((DIO_PORT_OUTPUT == PortDirection) || (DIO_PORT_INPUT == PortDirection)))
	{
		switch(PortId)
		{
			case 0:
			if(DIO_PORT_OUTPUT == PortDirection)
			{
				DDRA = 0xff;
			}
			else
			{
				DDRA = 0x00;
			}
			break;
			
			case 1:
			if(DIO_PORT_OUTPUT == PortDirection)
			{
				DDRB = 0xff;
			}
			else
			{
				DDRB = 0x00;
			}
			break;
			
			case 2:
			if(DIO_PORT_OUTPUT == PortDirection)
			{
				DDRC = 0xff;
			}
			else
			{
				DDRC = 0x00;
			}
			break;
			
			case 3:
			if(DIO_PORT_OUTPUT == PortDirection)
			{
				DDRD = 0xff;
			}
			else
			{
				DDRD = 0x00;
			}
			break;
		}
	}
}


void DIO_setPortValue(u8 PortId, u8 PortValue)
{
	if(PortId<=3)
	{
		switch(PortId)
		{
			case 0:
			PORTA = PortValue;
			break;
			
			case 1:
			PORTB = PortValue;
			break;
			
			case 2:
			PORTC = PortValue;
			break;
			
			case 3:
			PORTD = PortValue;
			break;
		}
	}
}


void DIO_getPortValue(u8 PortId, u8* PortValue)
{
	if((PortId<=3) && (PortValue != NULL))
	{
		switch(PortId)
		{
			case 0:
			*PortValue = PINA;
			break;
			
			case 1:
			*PortValue = PINB;
			break;
			
			case 2:
			*PortValue = PINC;
			break;
			
			case 3:
			*PortValue = PIND;
			break;
		}
	}		
}


void DIO_togglePortValue(u8 PortId)
{
	if(PortId<=3)
	{
		switch(PortId)
		{
			case 0:
			PORTA = ~PORTA;
			break;
			
			case 1:
			PORTB = ~PORTB;
			break;
			
			case 2:
			PORTC = ~PORTC;
			break;
			
			case 3:
			PORTD = ~PORTD;
			break;
		}
	}
}


void DIO_setInputPortResistance(u8 PortId)
{
	if(PortId<=3)
	{
		switch(PortId)
		{
			case 0:
			PORTA = 0xff;
			break;
			
			case 1:
			PORTB = 0xff;
			break;
			
			case 2:
			PORTC = 0xff;
			break;
			
			case 3:
			PORTD = 0xff;
			break;
		}
	}
}