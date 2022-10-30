/*
 * EXTI_program.c
 *
 * Created: 9/15/2022 12:01:31 PM
 *  Author: AMIT
 */ 

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"

/* MCAL */
#include "EXTI_interface.h"
#include "DIO_interface.h"

static void(*INT0pCallBack)(void) = NULL;
static void(*INT1pCallBack)(void) = NULL;
static void(*INT2pCallBack)(void) = NULL;

void EXTI_enable(EXTI_source interruptSource, EXTI_trigger interruptTriggerEdge)
{
	switch(interruptSource)
	{
		case EXTI_INT0:
		if(EXTI_RISING_EDGE == interruptTriggerEdge)
		{
			SET_BIT(MCUCR,0);
			SET_BIT(MCUCR,1);
		}
		else if(EXTI_FALLING_EDGE == interruptTriggerEdge)
		{
			CLR_BIT(MCUCR,0);
			SET_BIT(MCUCR,1);
		}
		else if(EXTI_LOW_LEVEL == interruptTriggerEdge)
		{
			CLR_BIT(MCUCR,0);
			CLR_BIT(MCUCR,1);
		}
		else if(EXTI_ANY_LOGICAL_CHANGE == interruptTriggerEdge)
		{
			SET_BIT(MCUCR,0);
			CLR_BIT(MCUCR,1);
		}
		
		SET_BIT(GICR,6); //enable INT0
		break;
		
		case EXTI_INT1:
		if(EXTI_RISING_EDGE == interruptTriggerEdge)
		{
			SET_BIT(MCUCR,2);
			SET_BIT(MCUCR,3);
		}
		else if(EXTI_FALLING_EDGE == interruptTriggerEdge)
		{
			CLR_BIT(MCUCR,2);
			SET_BIT(MCUCR,3);
		}
		else if(EXTI_LOW_LEVEL == interruptTriggerEdge)
		{
			CLR_BIT(MCUCR,2);
			CLR_BIT(MCUCR,3);
		}
		else if(EXTI_ANY_LOGICAL_CHANGE == interruptTriggerEdge)
		{
			SET_BIT(MCUCR,2);
			CLR_BIT(MCUCR,3);
		}
		
		SET_BIT(GICR,7); //enable INT1
		break;
		
		case EXTI_INT2:
		if(EXTI_RISING_EDGE == interruptTriggerEdge)
		{
			SET_BIT(MCUCSR,6);
		}
		else if(EXTI_FALLING_EDGE == interruptTriggerEdge)
		{
			CLR_BIT(MCUCSR,6);
		}
		
		SET_BIT(GICR,5); //enable INT2
		break;
	}
}


void EXTI_disable(EXTI_source interruptSource)
{
	switch(interruptSource)
	{
		case EXTI_INT0:
		CLR_BIT(GICR,6); //disable INT0
		break;
		
		case EXTI_INT1:
		CLR_BIT(GICR,7); //disable INT1
		break;
		
		case EXTI_INT2:
		CLR_BIT(GICR,5); //disable INT2
		break;
	}	
}


void EXTI_INT0SetCallBack(void(*ptr)(void))
{
	if(ptr != NULL)
	{
		INT0pCallBack = ptr;
	}
}


void EXTI_INT1SetCallBack(void(*ptr)(void))
{
	if(ptr != NULL)
	{
		INT1pCallBack = ptr;
	}
}


void EXTI_INT2SetCallBack(void(*ptr)(void))
{
	if(ptr != NULL)
	{
		INT2pCallBack = ptr;
	}
}


// ISR Function protoType for EXTI0
void __vector_1(void) __attribute__ ((signal));
void __vector_1(void)
{
	if(INT0pCallBack != NULL)
	{
		// Call action
		INT0pCallBack();
	}
}


// ISR Function protoType for EXTI1
void __vector_2(void) __attribute__ ((signal));
void __vector_2(void)
{
	if(INT1pCallBack != NULL)
	{
		// Call action
		INT1pCallBack();
	}
}


// ISR Function protoType for EXTI2
void __vector_3(void) __attribute__ ((signal));
void __vector_3(void)
{
	if(INT2pCallBack != NULL)
	{
		// Call action
		INT2pCallBack();
	}
}