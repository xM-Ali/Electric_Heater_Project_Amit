/*
 * Electric_Heater_Project_Amit.c
 *
 * Created: 10/30/2022 5:00:38 PM
 * Author : Ahmed Eldeeb
 */ 

/*UTILES*/
#define F_CPU 16000000UL
#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"

/*MCAL*/
#include "ADC_interface.h"
#include "GI_interface.h"
#include "DIO_interface.h"
#include "EXTI_interface.h"
#include "TMR_interface.h"
#include "TMR_config.h"
#include "I2C_INTERFACE.h"

/*HAL*/
#include "EEPROM_interface.h"
#include "FAN_INTERFACE.h"
#include "HEATING_ELEMENT_INTERFACE.h"
#include "LM35_INTERFACE.h"
#include "SSD_INTERFACE.h"

#include "main.h"

//Interrupts
void SitHigh();
void SitLow();
void OVF_Timer0(void);

//Variables
u8 Up_Button_Pressed;
u8 Down_Button_Pressed;
u8 Set_Mode;
u8 Enter_Set_Mode;
u8 Normal_mode;
u8 Set_Temprature=60;
u32 Sensor_temp;
u8 Number_Of_Presses;
//Average variables
u8 LM35_Reading = 0;
u8 Temprature_Array[10]; //FOR STORING THE LAST 10 READINGS INSTED OF EEPROM
u8 Temprature_Array_Counter = 0;
u8 Local_U8_Counter = 0;
u32 Local_U32_Sum = 0;
void A_Get_Average_Last_10_Readings(void);
int main(void)
{

	//TEMP SENSOR
	LM35_Init();
	//SEVEN SEGMENT DISPLAY
	SSD_Init();
	//COOLING ELEMENT INIT
	Fan_init();
	//HEATING ELEMENT INIT
	HEATING_ELEMENT_INIT();
	//EERPOM_INIT();
	TMR_timer0Init();
	TMR_timer0_OVF_SetCallBack(&OVF_Timer0);
	/* Replace with your application code */
	DIO_setPinDirection(DIO_PORTD,DIO_PIN2,DIO_PIN_INPUT);//Up Button
	DIO_setPinDirection(DIO_PORTD,DIO_PIN3,DIO_PIN_INPUT);//Down Button
	DIO_setPinDirection(DIO_PORTA,DIO_PIN1,DIO_PIN_INPUT);//Sensor
	//External Interrupt
	EXTI_INT0SetCallBack(&SitHigh);
	EXTI_INT1SetCallBack(&SitLow);
	//global interrupt enable
	GI_enable();
	EXTI_enable(EXTI_INT0,EXTI_FALLING_EDGE);
	EXTI_enable(EXTI_INT1,EXTI_FALLING_EDGE);



	Enter_Set_Mode=0;
	Set_Mode=0;
	Normal_mode=1;
	Number_Of_Presses=0;
	
	

	
	while (1)
	{
		Set_Mode=1;
		if(Enter_Set_Mode==1)
		{	//EEPROM_writeByte(50,Set_Temprature);
			Enter_Set_Mode=0;
			while (Set_Mode)
			{
				 DIO_togglePinValue(DIO_PORTB,DIO_PIN3);
				 _delay_ms(100);
				if (Number_Of_Presses==1)
				{
					//EEPROM_readeByte(50,Set_Temprature);
					SSD_WriteNumber(Set_Temprature);
				}
				else if (Number_Of_Presses>1)
				{
					//EEPROM_readeByte(50,Set_Temprature);
					if (Up_Button_Pressed == True)
					{
						TMR_timer0stop ();
						TMR_timer0start();
						//Range Of Set Between 35 to 75
						if(Set_Temprature<75)
						{
							Set_Temprature=Set_Temprature+5;
						}
						SSD_WriteNumber(Set_Temprature);
						Up_Button_Pressed=False;
					}
					
					//EEPROM_readeByte(50,Set_Temprature);
					if (Down_Button_Pressed == True)
					{
						TMR_timer0stop ();
						TMR_timer0start();
						if(Set_Temprature>35)
						{
							Set_Temprature=Set_Temprature-5;
						}
						SSD_WriteNumber(Set_Temprature);
						Down_Button_Pressed=False;
					}
				}
			}
			Number_Of_Presses=0;
			//EEPROM_writeByte(50,Set_Temprature);
		}
		if (Normal_mode==1)
		{	
			DIO_setPinValue(DIO_PORTB,DIO_PIN3,DIO_PIN_LOW);//SSD Blink off
			Sensor_temp=LM35_Read();//Get Temp From The sensor
			SSD_WriteNumber(Sensor_temp);
			
			//Heating
			if (Sensor_temp<Set_Temprature)
			{
				HEATING_ELEMENT_START();
				DIO_togglePinValue(DIO_PORTC,DIO_PIN7);
				Fan_SET_OFF();
			}
			
			//Cooling
			else if (Sensor_temp>Set_Temprature)
			{
				Fan_SET_ON();
				DIO_setPinValue(DIO_PORTC,DIO_PIN7,DIO_PIN_HIGH);
				HEATING_ELEMENT_STOP();
			}
			
			//Equal
			else
			{
				Fan_SET_OFF();
				DIO_setPinValue(DIO_PORTC,DIO_PIN7,DIO_PIN_LOW);
				HEATING_ELEMENT_STOP();
			}
		}
	}
}

void SitHigh(void)
{
	TMR_timer0start();
	Enter_Set_Mode=1;
	Up_Button_Pressed=True;
	Normal_mode=0;
	Number_Of_Presses++;
}

void SitLow(void)
{
	TMR_timer0start();
	Enter_Set_Mode=1;
	Down_Button_Pressed=True;
	Normal_mode=0;
	Number_Of_Presses++;
}


void OVF_Timer0(void)
{
	Set_Mode=0;
	Normal_mode=1;
}


//get last 10 average used in hardware
void A_Get_Average_Last_10_Readings(void)
{

	LM35_Reading = LM35_Read();
	Temprature_Array[Temprature_Array_Counter] = LM35_Reading;
	Temprature_Array_Counter++;


	if (Temprature_Array_Counter == 10)
	{
		Temprature_Array_Counter = 0;
		for (Local_U8_Counter = 0; Local_U8_Counter < 10; Local_U8_Counter++)
		{
			Local_U32_Sum += Temprature_Array[Local_U8_Counter];
		}
		Sensor_temp=Local_U32_Sum/10;
		Local_U32_Sum=0;
	}
}