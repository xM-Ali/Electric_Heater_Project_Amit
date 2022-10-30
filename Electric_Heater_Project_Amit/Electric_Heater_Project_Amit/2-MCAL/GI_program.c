/*
 * GI_program.c
 *
 * Created: 9/18/2022 9:44:17 AM
 *  Author: AMIT
 */ 

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"

/* MCAL */
#include "GI_interface.h"


void GI_enable (void)
{
	//global interrupt enable
	SET_BIT(SREG,7);
}


void GI_disable(void)
{
	CLR_BIT(SREG,7);
}