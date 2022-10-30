/*
 * TMR_interface.h
 *
 * Created: 9/22/2022 12:37:24 PM
 *  Author: AMIT
 */ 


#ifndef TMR_INTERFACE_H_
#define TMR_INTERFACE_H_

#define TMR_TMR0_NORMAL_MODE            1
#define TMR_TMR0_CTC_MODE               2
#define TMR_TMR0_FAST_PWM_MODE          3

#define TMR_ICU_FALLING_EDGE         0
#define TMR_ICU_RISING_EDGE          1


/* TIMER0 */
void TMR_timer0Init                 (void);
void TMR_timer0start                (void);
void TMR_timer0stop                 (void);
void TMR_timer0_OVF_SetCallBack     (void(*ptr)(void));
void TMR_timer0SetCompareMatchValue (u8 OCR0_Value);
void TMR_timer0_CTC_SetCallBack     (void(*ptr)(void));

/* TIMER1 */
void TMR_timer1Init                 (void);
void TMR_timer1start                (void);
void TMR_timer1stop                 (void);
void TMR_timer1SetCompareMatchAValue(u16 OCR1A_Value);

/* ICU */
void TMR_ICU_init(void);
void TMR_ICU_getTotalPeriod(u32* totalPeriod);
void TMR_ICU_getDutyCycle(u8* dutyCycle);


#endif /* TMR_INTERFACE_H_ */