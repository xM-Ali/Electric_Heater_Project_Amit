/*
 * TMR_config.h
 *
 * Created: 9/22/2022 12:37:32 PM
 *  Author: AMIT
 */ 


#ifndef TMR_CONFIG_H_
#define TMR_CONFIG_H_

/* Options FOR TMR0 Mode:
1- TMR_TMR0_NORMAL_MODE
2- TMR_TMR0_CTC_MODE
3- TMR_TMR0_FAST_PWM_MODE
*/

#define TMR_TMR0_MODE                      TMR_TMR0_NORMAL_MODE


#define TMR_TMR0_PRELOAD_VALUE               82

#define TMR_TMR0_OVERFLOW_COUNTER            3000

#define TMR_TMR0_CTC_COUNTER                 1000


/* Options FOR ICU STARTING EDGE:
1- TMR_ICU_RISING_EDGE
2- TMR_ICU_FALLING_EDGE*/
#define TMR_ICU_STARTING_EDGE           TMR_ICU_FALLING_EDGE

#endif /* TMR_CONFIG_H_ */