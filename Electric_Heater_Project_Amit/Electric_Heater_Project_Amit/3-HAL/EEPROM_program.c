/*
 * EEPROM_program.c
 *
 * Created: 10/9/2022 11:18:34 AM
 *  Author: AMIT
 */ 


#define F_CPU   16000000UL
#include <util/delay.h>

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"

/* MCAL */
#include "I2C_INTERFACE.h"

/* HAL */
#include "EEPROM_interface.h"

void EERPOM_INIT(void)
{
	I2C_initMaster();
	_delay_ms(1000);
}


void EEPROM_writeByte(u16 byteAddress,u8 data)
{
	u8 address = (u8)(EEPROM_FIXED_ADDRESS | (u8)(byteAddress>>8));
	
	// Send start condition
	I2C_Send_StartCondition();
	
	// Send slave address with write operation
	I2C_Send_Slave_Address_Write(address);
	
	// Send byte address
	I2C_SendMasterDataByte((u8)byteAddress);
	
	// Send byte data
	I2C_SendMasterDataByte(data);
	
	// Send stop condition
	I2C_Send_StopCondition();
	
	_delay_ms(5);
}


void EEPROM_readByte(u16 byteAddress,u8* returnedData)
{
	u8 address = (u8)(EEPROM_FIXED_ADDRESS | (u8)(byteAddress>>8));
	
	// Send start condition
	 I2C_Send_StartCondition;
	
	// Send slave address with write operation
	I2C_Send_Slave_Address_Write(address);
	
	// Send byte address
	I2C_SendMasterDataByte((u8)byteAddress);
	
	// Send repeated start
	 I2C_Repeated_StartCondition();
	
	// Send slave address with read operation
	 I2C_Send_Slave_Address_Read(address);
	
	// Read byte data
	I2C_ReadMasterDataByte(returnedData);
	
	// Send stop condition
	I2C_Send_StopCondition();
	
	_delay_ms(5);
}