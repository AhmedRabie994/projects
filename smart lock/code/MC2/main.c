/*
 * main.c
 *
 *  Created on: Jan 31, 2020
 *      Author: user1
 */
////////////////////////MC2////////////////////////////////////////////////////////////////////


#include "DRIVER/UART.h"
#include "DRIVER/I2C.h"
#include "DRIVER/TIMER.h"
////////////////////////MC2////////////////////////////////////////////////////////////////////



#define EEPROM_Write_Addess		0xA0
#define EEPROM_Read_Addess		0xA1


#define frist_time              0x10
#define normal_mode             0x11
#define change_password         0x12
#define open_thedoor            0x13
#define password_is_saved       0x14
#define password_is_matched     0x15
#define password_isnot_matched  0x17
#define password_error_3t       0x16

////////////////////////MC2////////////////////////////////////////////////////////////////////


uint8 CompareArray(uint8 *a_Array1,uint8 *a_Array2);
void eeprom_read_massage(uint8 *a_mass);
void eeprom_write_massage(uint8 *a_mass);
void eeprom_write_byte(uint8 a_data);
uint8 eeprom_read_byte();
void first_time_comp();
void normal_mod_FUNC();
void opend_door_FUNC();
void change_pass_FUNC();



////////////////////////MC2////////////////////////////////////////////////////////////////////



//uint8 g_f_o_password[6];
//uint8 g_f_n_password[6];
//uint8 g_password[6];


////////////////////////MC2////////////////////////////////////////////////////////////////////

int main(void){
    uint8 data='a';
    DDRA=0xff;
	TIMER_ConfigType TIMER_config={NORMAL,F_CPU_1024,ctc_N};
	TIMER_Init(&TIMER_config);
	UART_init();
	I2C_Init();
	data=eeprom_read_byte();
	if(!(data>= '0' && data <='9'))
	{
	eeprom_write_byte('A');}
while(1){
	_delay_ms(25);
	data=eeprom_read_byte();
     if (data=='A'){
     UART_sendByte(frist_time);
     first_time_comp();
     }
    else {
    UART_sendByte(normal_mode);
    normal_mod_FUNC();

}}
	return 0;
}

void eeprom_write_byte(uint8 a_data){
	I2C_Start(EEPROM_Write_Addess);   /* Start I2C with device write address */
				I2C_Write(0x00);                /* Write start memory address for data write */
			    I2C_Write(a_data);
		        I2C_Stop();			              /* Stop I2C */
	}

uint8 eeprom_read_byte(){
	uint8 a_data;
	I2C_Start(EEPROM_Write_Addess);   /* Start I2C with device write address */
			I2C_Write(0x00);
			I2C_Repeated_Start(EEPROM_Read_Addess);	            /* Write start memory address */
			a_data=I2C_Read_Nack();	/* Read flush data with nack */
			I2C_Stop();
			return a_data;
}

void eeprom_write_massage(uint8 *a_mass){
	I2C_Start(EEPROM_Write_Addess);   /* Start I2C with device write address */
			I2C_Write(0x00);                /* Write start memory address for data write */
	        for (int i=0;i<6;i++)/* Write array data */
	        {
		        I2C_Write(a_mass[i]);
	        }
	        I2C_Stop();			              /* Stop I2C */
}

void eeprom_read_massage(uint8 *a_mass){
	I2C_Start(EEPROM_Write_Addess);   /* Start I2C with device write address */
			I2C_Write(0x00);
			I2C_Repeated_Start(EEPROM_Read_Addess);	            /* Write start memory address */
			for (int i = 0; i<5; i++)                /* Read data with acknowledgment */
			{
			a_mass[i]=I2C_Read_Ack();
			}
		    I2C_Read_Nack();	/* Read flush data with nack */
			I2C_Stop();
}

uint8 CompareArray(uint8 *a_Array1,uint8 *a_Array2)
{
	int i;
	for(i=0;i<6;i++)
	{
		if(a_Array1[i] != a_Array2[i])
		{
			/* if only one element in Array1 does not match the corresponding element in Array2 return 1 */
			return 1;
		}
	}
	/* both arrays are identical retrun 0*/
	return 0;
}

void first_time_comp(){
	uint8 o_password[10],N_password[10];
	uint8 l_data;
	UART_receiveString(o_password);
	eeprom_write_massage(o_password);
	_delay_ms(20);
	eeprom_read_massage(N_password);
	UART_receiveString(N_password);
	l_data=CompareArray(N_password,o_password);
    if(!l_data){
    UART_sendByte(password_is_saved);
    normal_mod_FUNC();
    }
    else if(l_data==1){
    UART_sendByte(password_isnot_matched);
    first_time_comp();
    }
}

void normal_mod_FUNC(){
	uint8 state;
state=UART_recieveByte();
	switch(state){
	case change_password: change_pass_FUNC();break;
	case open_thedoor:	opend_door_FUNC(); break;
	default:normal_mod_FUNC();break;
	}

}

void change_pass_FUNC(){
	uint8 OL_password[7]={0},NE_password[7]={0};
	static uint8 l_count=0;
		uint8 l_state;
		_delay_ms(20);
		UART_receiveString(NE_password);
		eeprom_read_massage(OL_password);
		l_state=CompareArray(OL_password,NE_password);
		if (l_count>1){
			l_count=0;
			UART_sendByte(password_error_3t);
			SET_BIT(PORTA,2);
			timer_delay_Ms(60000);
			UART_sendByte(normal_mode);
			CLEAR_BIT(PORTA,2);
			normal_mod_FUNC();}
    if(!(l_state))
			{UART_sendByte(password_is_matched);
			UART_receiveString(NE_password);
			eeprom_write_massage(NE_password);
            _delay_ms(20);
			UART_sendByte(normal_mode);
			normal_mod_FUNC();
			}
	else if(l_state==1){
            UART_sendByte(password_isnot_matched);
			_delay_ms(2000);
			l_count++;
			UART_sendByte(open_thedoor);
			change_pass_FUNC();
				}
			}






void opend_door_FUNC(){
	uint8 l_password[7],g_password[7];
	static uint8 l_count=0;
	uint8 l_state;
	_delay_ms(20);
	UART_receiveString(g_password);
	eeprom_read_massage(l_password);
	l_state=CompareArray(g_password,l_password);
	if (l_count>1){
		l_count=0;
		UART_sendByte(password_error_3t);
		SET_BIT(PORTA,2);
		timer_delay_Ms(60000);
		UART_sendByte(normal_mode);
		CLEAR_BIT(PORTA,2);
		normal_mod_FUNC();}
	if(!(l_state))
	{l_count=0;
	UART_sendByte(password_is_matched);
	SET_BIT(PORTA,0);
	CLEAR_BIT(PORTA,1);
	_delay_ms(15000);
	SET_BIT(PORTA,1);
	CLEAR_BIT(PORTA,0);
	_delay_ms(15000);
	CLEAR_BIT(PORTA,0);
	CLEAR_BIT(PORTA,1);
	UART_sendByte(normal_mode);
	normal_mod_FUNC();
	}

	else if(l_state==1){

		UART_sendByte(password_isnot_matched);
		_delay_ms(2000);
		l_count++;
		UART_sendByte(open_thedoor);
	    opend_door_FUNC();
	}
}






