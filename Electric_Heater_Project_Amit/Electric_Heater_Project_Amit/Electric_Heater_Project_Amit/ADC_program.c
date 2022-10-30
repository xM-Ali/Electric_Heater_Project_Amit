/*
 * ADC_program.c
 *
 * Created: 9/20/2022 12:41:54 PM
 *  Author: AMIT
 */ 


 /* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"

/* MCAL */
#include "ADC_interface.h"


void ADC_init(void)
{
	// Select Vref = AVCC
	SET_BIT(ADMUX,6);
	CLR_BIT(ADMUX,7);
	
	// Select Right Adjustment
	CLR_BIT(ADMUX,5);
	
	// Single Conversation Mode
	CLR_BIT(ADCSRA,5);
	
	// Prescaler 128 For 16MHZ
	SET_BIT(ADCSRA,0);
	SET_BIT(ADCSRA,1);
	SET_BIT(ADCSRA,2);
	
	// ADC Enable
	SET_BIT(ADCSRA,7);
}


void ADC_getDigitalValue(u8 channelNum, u32* digitalValue)
{
	if((channelNum<32) && (digitalValue != NULL))
	{
		//Clear ADMUX Channel Bits
		ADMUX &= 0b11100000;

		// Select Channel Number
		ADMUX |= channelNum;
		
		// Start Conversition
		SET_BIT(ADCSRA,6);
		
		// Wait For The Flag Of ADC
		while(0 == GET_BIT(ADCSRA,4));
		
		// Clear Flag
		SET_BIT(ADCSRA,4);
		
		// Read Digital Value
		*digitalValue = ADC_u16;
	}
}