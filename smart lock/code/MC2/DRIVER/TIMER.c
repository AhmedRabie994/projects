/******************************************************************************
 *
 * Module: TIMER
 *
 * File Name: TIMER.c
 *
 * Description: Source file for the AVR TIMER driver
 *
 * Author: Ahmed Rabie
 *
 *******************************************************************************/
#include"TIMER.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TIMER0_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/
void TIMER_Init(const TIMER_ConfigType *Config_Ptr){
	/*Compare Output Mode, non-PWM Mode:
	 *0 0 0 Normal port operation, OC0 disconnected.
	  1 0 1 Toggle OC0 on compare match
	  2 1 0 Clear OC0 on compare match
	  3 1 1 Set OC0 on compare match
	 */
	switch((Config_Ptr->MODE)){
		case 0:{CLEAR_BIT(TCCR0,WGM00);CLEAR_BIT(TCCR0,WGM01);break;}
		case 1:{SET_BIT(TCCR0,WGM00);CLEAR_BIT(TCCR0,WGM01);break;}
		case 2:{CLEAR_BIT(TCCR0,WGM00);SET_BIT(TCCR0,WGM01);break;}
		case 3:{SET_BIT(TCCR0,WGM00);SET_BIT(TCCR0,WGM01);break;}
	}
/*TIMER Mode description:
 *0 0 0 Normal 0xFF Immediate MAX
  1 0 1 PWM, Phase Correct 0xFF TOP BOTTOM
  2 1 0 CTC OCR0 Immediate MAX
  3 1 1 Fast PWM 0xFF BOTTOM MAX
*/
/*
 * Compare Output Mode, Phase Correct PWM Mode:
 0 0 Normal port operation, OC0 disconnected.
 0 1 Reserved
 1 0 Clear OC0 on compare match when up-counting. Set OC0 on compare
     match when downcounting.
 1 1 Set OC0 on compare match when up-counting. Clear OC0 on compare
     match when downcounting.

 ***********************************************/
	TCCR0|=((Config_Ptr->SCALER)<<CS00)|((Config_Ptr->TCM)<<COM00);
	TIMSK|=(1<<TOIE0);
	sei();
}

void TIMER_setCallBack(void(*a_ptr)(void)){

	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}

void TIMER_Set(uint8 a_Timer_value){
	TCNT0=a_Timer_value;
}
void PWM_Set(uint8 a_PWM_value){
OCR0=a_PWM_value;
}
void TIMER_Enable(const TIMER_ConfigType * Config_Ptr){
	TCCR0|=((Config_Ptr->SCALER)<<COM00);
}

void TIMER_disable(){
	TCCR0|=0XF8;

}
void timer_delay_Ms(uint32 a_timer_value){
int i=0;
		do{
		if(TCNT0>=7){
		TCNT0=0;
		i++;
		}
		}while(i< a_timer_value);
	}



