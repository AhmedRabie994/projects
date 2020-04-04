/******************************************************************************
 *
 * Module: TIMER_8BIT
 *
 * File Name: TIMER_8BIT.h
 *
 * Description: header file for the ATmega16 TIMER_8BIT driver
 *
 * Author: Ahmed Rabie
 *
 *******************************************************************************/


#ifndef TIMER_H_
#define TIMER_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024,Clock_Falling_edge,Clock_Rising_edge
}TIMER_PRESCALER;

/*TIMER Mode description:
 *0 0 0 Normal 0xFF Immediate MAX
  1 0 1 PWM, Phase Correct 0xFF TOP BOTTOM
  2 1 0 CTC OCR0 Immediate MAX
  3 1 1 Fast PWM 0xFF BOTTOM MAX
*/
typedef enum
{
	 NORMAL,PWM,CTC,F_PWM
}TIMER_MODE;

/*
 * Compare Output Mode, Phase Correct PWM Mode:
 0 0 Normal port operation, OC0 disconnected.
 0 1 Reserved
 1 0 Clear OC0 on compare match when up-counting. Set OC0 on compare
     match when downcounting.
 1 1 Set OC0 on compare match when up-counting. Clear OC0 on compare
     match when downcounting.
 ***********************************************
Compare Output Mode, non-PWM Mode:
 *0 0 0 Normal port operation, OC0 disconnected.
  1 0 1 Toggle OC0 on compare match
  2 1 0 Clear OC0 on compare match
  3 1 1 Set OC0 on compare match
 */
typedef enum
{
	ctc_N,Toggle,Clear,Set
}TIMER_Compare_Match;

typedef struct
{
	TIMER_MODE MODE;
	TIMER_PRESCALER SCALER;
	TIMER_Compare_Match TCM;

}TIMER_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description : Function to initialize the ICU driver
 * 	1. Set the required Mode.
 * 	2. Set the required clock.
 * 	3. Set the required TIMER Compare Match Mode.
 *
 */
void TIMER_Init(const TIMER_ConfigType * Config_Ptr);
/*
 * Description: Function to set the Call Back function address.
 */
void TIMER_setCallBack(void(*a_ptr)(void));

/*
Description : Function to set timer value(TCNT);
*/
void TIMER_Set(uint8 a_Timer_value);
/*
Description : Function to set PWM value(OCR);
*/
void PWM_Set(uint8 a_PWM_value);
/*
Description : Function to enable the timer;
*/
void TIMER_Enable();
/*
Description : Function to disable the timer;
*/
void TIMER_disable();
/*Description : Function to make a delay in MS by using timer*/
void timer_delay_Ms(uint32 a_timer_value);

#endif /* TIMER_H_ */
