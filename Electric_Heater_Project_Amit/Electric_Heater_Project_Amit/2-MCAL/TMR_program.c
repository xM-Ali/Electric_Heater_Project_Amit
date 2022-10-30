/*
 * TMR_program.c
 *
 * Created: 9/22/2022 12:37:16 PM
 *  Author: AMIT
 */ 

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"

/* MCAL */
#include "TMR_interface.h"
#include "TMR_config.h"


static void(*TMR_timer0_Ovf_pCallBack)(void) = NULL;
static void(*TMR_timer0_ctc_pCallBack)(void) = NULL;

volatile static u16 TMR_ICU_onPeriod,TMR_ICU_offPeriod;



/* TIMER0 */
void TMR_timer0Init(void)
{
#if TMR_TMR0_MODE == TMR_TMR0_NORMAL_MODE
	// Select Mode = Normal Mode
	CLR_BIT(TCCR0,6);
	CLR_BIT(TCCR0,3);
	
	// Init Timer With Preload Value
	TCNT0 = TMR_TMR0_PRELOAD_VALUE;
	
	// Enable OVF Interrupt
	SET_BIT(TIMSK,0);
	
#elif TMR_TMR0_MODE == TMR_TMR0_CTC_MODE
	// Select Mode = CTC Mode
	CLR_BIT(TCCR0,6);
	SET_BIT(TCCR0,3);
	
	// Enable CTC Interrupt
	SET_BIT(TIMSK,1);
	
#elif TMR_TMR0_MODE == TMR_TMR0_FAST_PWM_MODE
    // Select Mode = Fast PWM Mode
	SET_BIT(TCCR0,6);
	SET_BIT(TCCR0,3);
	
	// Select Non Inverting Mode
	CLR_BIT(TCCR0,4);
	SET_BIT(TCCR0,5);
#endif
}


void TMR_timer0start(void)
{
    // Select Prescaler Value = 64
	SET_BIT(TCCR0,0);
	SET_BIT(TCCR0,1);
	CLR_BIT(TCCR0,2);
}


void TMR_timer0stop(void)
{
	CLR_BIT(TCCR0,0);
	CLR_BIT(TCCR0,1);
	CLR_BIT(TCCR0,2);
}


void TMR_timer0SetCompareMatchValue(u8 OCR0_Value)
{
	// Init Timer With Compare Value
	OCR0 = OCR0_Value;
}


void TMR_timer0_OVF_SetCallBack(void(*ptr)(void))
{
	if(ptr != NULL)
	{
		TMR_timer0_Ovf_pCallBack = ptr;
	}
}


void TMR_timer0_CTC_SetCallBack(void(*ptr)(void))
{
	if(ptr != NULL)
	{
		TMR_timer0_ctc_pCallBack = ptr;
	}
}


// ISR Function protoType for TMR0 OVF
void __vector_11(void) __attribute__ ((signal));
void __vector_11(void)
{
	static u16 counterOVF=0;
	++counterOVF;
	
	if(TMR_TMR0_OVERFLOW_COUNTER == counterOVF)
	{
		// Set Preload Value
		TCNT0 = TMR_TMR0_PRELOAD_VALUE;
		
		// Clear Counter
		counterOVF = 0;
		
		//call action
		if(TMR_timer0_Ovf_pCallBack != NULL)
		{
			TMR_timer0_Ovf_pCallBack();
		}
	}
}


// ISR Function protoType for TMR0 CTC
void __vector_10(void) __attribute__ ((signal));
void __vector_10(void)
{
	static u16 counterCTC=0;
	++counterCTC;
	
	if (TMR_TMR0_CTC_COUNTER == counterCTC)
	{
		// Clear Counter
		counterCTC = 0;
		
		//call action
		if(TMR_timer0_ctc_pCallBack != NULL)
		{
			TMR_timer0_ctc_pCallBack();
		}
	}
}


/* TIMER1 */
void TMR_timer1Init(void)
{
	// Select Mode = Fast PWM Mode(14)
	CLR_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	SET_BIT(TCCR1B,4);
	
	// Select Non Inverting Mode
	CLR_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
	
	// ICR1 >> period time = 20ms >> freq. = 50HZ
	ICR1_u16 = 4999;
}


void TMR_timer1start(void)
{
	// Select Prescaler Value = 64
	SET_BIT(TCCR1B,0);
	SET_BIT(TCCR1B,1);
	CLR_BIT(TCCR1B,2);
}


void TMR_timer1stop(void)
{
	CLR_BIT(TCCR1B,0);
	CLR_BIT(TCCR1B,1);
	CLR_BIT(TCCR1B,2);
}


void TMR_timer1SetCompareMatchAValue(u16 OCR1A_Value)
{
	// Init Timer With Compare Value
	OCR1A_u16 = OCR1A_Value;
}



/* ICU */
void TMR_ICU_init(void)
{
	// Select Mode = Normal Mode
    CLR_BIT(TCCR1A,0);
	CLR_BIT(TCCR1A,1);
	CLR_BIT(TCCR1B,3);
	CLR_BIT(TCCR1B,4);
	
	// select edge source of ICP1 interrupt
#if TMR_ICU_STARTING_EDGE == TMR_ICU_RISING_EDGE  
    SET_BIT(TCCR1B,6);
#elif TMR_ICU_STARTING_EDGE == TMR_ICU_FALLING_EDGE 
	CLR_BIT(TCCR1B,6);
#endif
	// activate ICU interrupt
	SET_BIT(TIMSK,5);
	
	// Select Prescaler Value = 64
	SET_BIT(TCCR1B,0);
	SET_BIT(TCCR1B,1);
	CLR_BIT(TCCR1B,2);
}


void TMR_ICU_getTotalPeriod(u32* totalPeriod)
{
	*totalPeriod = (u32)(TMR_ICU_onPeriod+TMR_ICU_offPeriod);
}


void TMR_ICU_getDutyCycle(u8* dutyCycle)
{
	*dutyCycle = (u8)((TMR_ICU_onPeriod)/(TMR_ICU_onPeriod+TMR_ICU_offPeriod));
}


// ISR Function protoType for TMR1 ICU 
void __vector_6(void) __attribute__ ((signal)); 
void __vector_6(void)
{
	static u8  flag = TMR_ICU_STARTING_EDGE;
	static u16 oldValue;
	static u16 CounterValue;
	
	/* Read ICR1 value*/
	CounterValue = ICR1_u16;
	
	if (flag == TMR_ICU_RISING_EDGE) //calculate off period
	{
		TMR_ICU_offPeriod = (CounterValue - oldValue)*4;
		// change edge source of ICP1 interrupt to falling edge  
		CLR_BIT(TCCR1B,6);
		// change flag value
		flag = TMR_ICU_FALLING_EDGE;
	}
	else if (flag == TMR_ICU_FALLING_EDGE) //calculate on period
	{
		TMR_ICU_onPeriod = (CounterValue - oldValue)*4;
		// change edge source of ICP1 interrupt to rising edge  
		SET_BIT(TCCR1B,6);
		// change flag value
		flag = TMR_ICU_RISING_EDGE;
	}
	// old value
	oldValue = CounterValue;
}