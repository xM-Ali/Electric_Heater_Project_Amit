/*
 * I2C_PROGRAM.c
 *
 * Created: 10/6/2022 12:11:37 PM
 *  Author: AHMED ELDEEB
 */ 
#define F_CPU 16000000UL
#include <util/delay.h>

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"

/*MCALL*/
#include "I2C_INTERFACE.h"


void I2C_initMaster(void)
{
	// Set prescalar = 1 >> set freq ==400KHZ
	
	CLR_BIT(TWSR,0);
	CLR_BIT(TWSR,1);
	TWBR =12;
	
	//Enable Acknowledge
	SET_BIT(TWCR,6);
	
	// Enable TWI
	SET_BIT(TWCR,2);
	
}

void I2C_initSlave(u8 SlaveAddress)
{
	if (SlaveAddress<128)
	{
		//SET Slave Address
		TWAR=SlaveAddress<<1;
		
		//Disable General Code
		CLR_BIT(TWAR,0);	
		
		//Enable Acknowledge
		SET_BIT(TWCR,6);
		
		// Enable TWI
		SET_BIT(TWCR,2);	
	}
}

void I2C_Send_StartCondition(void)
{
	//Send Start Condition
	SET_BIT(TWCR,5);
	
	//Clear Flag To Start Current Job
	SET_BIT(TWCR,7);
	
	//Wait For The Flag
	while(0==GET_BIT(TWCR,7));
	
	//Check Ack==SC Ack
	while((TWSR & 0xF8)!=0x08);	
}

void I2C_Repeated_StartCondition(void)
{
	//Send Start Condition
	SET_BIT(TWCR,5);
	
	//Clear Flag To Start Current Job
	SET_BIT(TWCR,7);
	
	//Wait For The Flag
	while(0==GET_BIT(TWCR,7));
	
	//Check Ack==Repeated Start Ack
	while((TWSR & 0xF8)!=0x10);
}

void I2C_Send_StopCondition(void)
{
	//Send Stop Condition
	SET_BIT(TWCR,4);
	
	//Clear Flag To Start Current Job
	SET_BIT(TWCR,7);
}

void I2C_Send_Slave_Address_Write(u8 slave_address)
{
	//Send Address
	TWDR=slave_address<<1;
	
	//Select Read Operation
	CLR_BIT(TWDR,0);
	
	//To Init Start Condition
	CLR_BIT(TWCR,5);
	
	//Clear Flag To Start Current Job
	SET_BIT(TWCR,7);
	
	//Wait For The Flag
	while(0==GET_BIT(TWCR,7));
	
	//Check Ack==MMaster transmit ( slave address + Write request ) ACK
	while((TWSR & 0xF8)!=0x18);
}

void I2C_Send_Slave_Address_Read(u8 slave_address)
{
	//Send Address
	TWDR=slave_address<<1;
	
	//Select Read Operation
	SET_BIT(TWDR,0);
	
	//To Init Start Condition
	CLR_BIT(TWCR,5);
	
	//Clear Flag To Start Current Job
	SET_BIT(TWCR,7);
	
	//Wait For The Flag
	while(0==GET_BIT(TWCR,7));
	
	//Check Ack==MMaster transmit ( slave address + Read request ) ACK
	while((TWSR & 0xF8)!=0x40);
}

void I2C_SendMasterDataByte(u8 TxData)
{
	//Write data into data Register
	TWDR=TxData;
	
	//Clear Flag To Start Current Job
	SET_BIT(TWCR,7);
	
	//Wait For The Flag
	while(0==GET_BIT(TWCR,7));
	
	//Check Ack==Master transmit data ACK
	while((TWSR & 0xF8)!=0x28);
}

void I2C_ReadMasterDataByte(u8* RxData)
{
	if (RxData!= NULL)
	{
		//Clear Flag To Start Current Job
		SET_BIT(TWCR,7);
		
		//Wait For The Flag
		while(0==GET_BIT(TWCR,7));
		
		//Check Ack==Master recieve data ACK
		while((TWSR & 0xF8)!=0x50);
		
		//Read Data 
		*RxData=TWDR;
	}
}