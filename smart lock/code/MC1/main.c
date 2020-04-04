/*
 * main.c
 *
 *  Created on: Jan 30, 2020
 *      Author: user1
 */


////////////////////////MC1////////////////////////////////////////////////////////////////////

#include "DRIVER/LCD.h"
#include "DRIVER/UART.h"
#include "DRIVER/KEYPAD.h"
#include "DRIVER/TIMER.h"

////////////////////////MC1////////////////////////////////////////////////////////////////////

#define frist_time              0x10
#define normal_mode             0x11
#define change_password         0x12
#define open_thedoor            0x13
#define password_is_saved       0x14
#define password_is_matched     0x15
#define password_isnot_matched  0x17
#define password_error_3t       0x16

////////////////////////MC1////////////////////////////////////////////////////////////////////


void take_pass(uint8 *pass);
void frist_time_FUNC();
void normal_mod_FUNC();
void opend_door_FUNC();
void change_pass_FUNC();

////////////////////////MC1////////////////////////////////////////////////////////////////////


int main(void){
	uint8 state;
	TIMER_ConfigType TIMER_config={NORMAL,F_CPU_1024,ctc_N};
	TIMER_Init(&TIMER_config);
	UART_init();    //initialize the UART driver.
	LCD_init();    //initialize the lcd driver.
  while(1){
	  state=UART_recieveByte();
	if(state==normal_mode){//wait until MC2 is ready
	  normal_mod_FUNC();}
	  else if(state==frist_time)//wait until MC2 is ready
	 {frist_time_FUNC();}
	  }
  return 0;
}

////////////////////////MC1////////////////////////////////////////////////////////////////////


void take_pass(uint8 *pass){
	uint8 i=0;
	uint8 key;
	do{
	key=KeyPad_getPressedKey();
	switch(key){
	case 7:{LCD_gotoRowColumn(2,1+i); pass[i]='7';LCD_displayCharacter(pass[i]);_delay_ms(250);LCD_gotoRowColumn(2,1+i);LCD_displayCharacter('X');i++;break;}
	case 8:{LCD_gotoRowColumn(2,1+i); pass[i]='8';LCD_displayCharacter(pass[i]);_delay_ms(250);LCD_gotoRowColumn(2,1+i);LCD_displayCharacter('X');i++;break;}
	case 9:{LCD_gotoRowColumn(2,1+i); pass[i]='9';LCD_displayCharacter(pass[i]);_delay_ms(250);LCD_gotoRowColumn(2,1+i);LCD_displayCharacter('X');i++;break;}
	case 4:{LCD_gotoRowColumn(2,1+i); pass[i]='4';LCD_displayCharacter(pass[i]);_delay_ms(250);LCD_gotoRowColumn(2,1+i);LCD_displayCharacter('X');i++;break;}
	case 5:{LCD_gotoRowColumn(2,1+i); pass[i]='5';LCD_displayCharacter(pass[i]);_delay_ms(250);LCD_gotoRowColumn(2,1+i);LCD_displayCharacter('X');i++;break;}
	case 6:{LCD_gotoRowColumn(2,1+i); pass[i]='6';LCD_displayCharacter(pass[i]);_delay_ms(250);LCD_gotoRowColumn(2,1+i);LCD_displayCharacter('X');i++;break;}
	case 1:{LCD_gotoRowColumn(2,1+i); pass[i]='1';LCD_displayCharacter(pass[i]);_delay_ms(250);LCD_gotoRowColumn(2,1+i);LCD_displayCharacter('X');i++;break;}
	case 2:{LCD_gotoRowColumn(2,1+i); pass[i]='2';LCD_displayCharacter(pass[i]);_delay_ms(250);LCD_gotoRowColumn(2,1+i);LCD_displayCharacter('X');i++;break;}
	case 3:{LCD_gotoRowColumn(2,1+i);pass[i]='3';LCD_displayCharacter(pass[i]);_delay_ms(250);LCD_gotoRowColumn(2,1+i);LCD_displayCharacter('X');i++;break;}
	case 0:{LCD_gotoRowColumn(2,1+i); pass[i]='0';LCD_displayCharacter(pass[i]);_delay_ms(250);LCD_gotoRowColumn(2,1+i);LCD_displayCharacter('X');i++;break;}
	case '=':{LCD_gotoRowColumn(2,1+i); pass[i]='#';i=6;i++;break;}
	default: break;
	}
	}
	while(i<6);
	//pass[i]='\0';
}

void frist_time_FUNC(){
    uint8 old[7],new[7];
    uint8 state;
	LCD_gotoRowColumn(1,1);
	LCD_print_str("enter the new pass:");
	LCD_gotoRowColumn(2,1);
	take_pass(old);
	old[7]='\0';
	UART_sendString(old);
	LCD_clearScreen();
	LCD_gotoRowColumn(1,1);
	LCD_print_str("repeat the new pass:");
	LCD_gotoRowColumn(2,1);
	take_pass(new);
	new[7]='\0';
	UART_sendString(new);
	_delay_ms(20);
	state=UART_recieveByte();
	if(state==password_is_saved){
	UART_sendByte(normal_mode);
	LCD_clearScreen();
	LCD_gotoRowColumn(1,1);
	LCD_print_str("pass has save");
	_delay_ms(1000);
	normal_mod_FUNC();}
	else if(state==password_isnot_matched)
	{LCD_clearScreen();
	LCD_gotoRowColumn(1,1);
	LCD_print_str("pass error");
	LCD_gotoRowColumn(2,1);
	LCD_print_str("try again");
	_delay_ms(500);
	LCD_clearScreen();
	frist_time_FUNC();
	}
}

void normal_mod_FUNC(){
	uint8 state;
	LCD_gotoRowColumn(1,1);
	LCD_print_str("+:change pass");
	LCD_gotoRowColumn(2,1);
	LCD_print_str("-:open door");
	state=KeyPad_getPressedKey();
switch(state){
	case '+':{LCD_clearScreen();UART_sendByte(change_password);change_pass_FUNC();break;}
	case '-':{LCD_clearScreen();UART_sendByte(open_thedoor); opend_door_FUNC();break;}
	default:normal_mod_FUNC();break;
}
}

void opend_door_FUNC(){
	uint8 l_password[7]={0};
	uint8 l_state=0;
	LCD_gotoRowColumn(1,1);
	LCD_print_str("enter the pass");
	LCD_gotoRowColumn(2,1);
	take_pass(l_password);
	l_password[7]='\0';
	UART_sendString(l_password);
	l_state=UART_recieveByte();
	if(l_state==password_is_matched){
		LCD_clearScreen();
		LCD_gotoRowColumn(1,1);
		LCD_print_str("door is opening>>>>>");
		l_state=UART_recieveByte();
		if(l_state==normal_mode){
		LCD_clearScreen();
		normal_mod_FUNC();}
	}
	else if(l_state==password_isnot_matched){
		l_state=0;
		LCD_clearScreen();
		LCD_gotoRowColumn(1,1);
		LCD_print_str("try again");
		l_state=UART_recieveByte();
		if(l_state==open_thedoor){
			LCD_clearScreen();
			opend_door_FUNC();
		}
	 }
	else if(l_state==password_error_3t){
			LCD_clearScreen();
			LCD_gotoRowColumn(1,3);
			LCD_print_str("3time error.....");
			LCD_gotoRowColumn(2,3);
		    LCD_print_str("3time error.....");
		    l_state=UART_recieveByte();
		    if(l_state==normal_mode){
		   	LCD_clearScreen();
			normal_mod_FUNC();}
					}
}

void change_pass_FUNC(){
	uint8 old[7]={0},new[7]={0};
	uint8 state;
	    LCD_clearScreen();
		LCD_gotoRowColumn(1,1);
		LCD_print_str("enter the old pass:");
		LCD_gotoRowColumn(2,1);
		take_pass(old);
		old[7]='\0';
		UART_sendString(old);
		state=UART_recieveByte();
		if(state==password_is_matched){
		LCD_clearScreen();
		LCD_gotoRowColumn(1,1);
		LCD_print_str("pass is right");
		_delay_ms(1000);
		LCD_clearScreen();
		LCD_gotoRowColumn(1,1);
		LCD_print_str("enter the new pass:");
		LCD_gotoRowColumn(2,1);
		take_pass(new);
		new[7]='\0';
		UART_sendString(new);
		LCD_clearScreen();
		LCD_gotoRowColumn(1,1);
		LCD_print_str("pass has saved");
		state=UART_recieveByte();
		if(state==normal_mode){
			LCD_clearScreen();
			normal_mod_FUNC();
		}
		}
		else if(state==password_isnot_matched){
			    state=0;
				LCD_clearScreen();
				LCD_gotoRowColumn(1,1);
				LCD_print_str("try again");
				state=UART_recieveByte();
				if(state==open_thedoor){
					LCD_clearScreen();
					change_pass_FUNC();
				}
			 }
			else if(state==password_error_3t){
					LCD_clearScreen();
					LCD_gotoRowColumn(1,3);
					LCD_print_str("3time error.....");
					LCD_gotoRowColumn(2,3);
				    LCD_print_str("3time error.....");
				    state=UART_recieveByte();
				    if(state==normal_mode){
				   	LCD_clearScreen();
					normal_mod_FUNC();}
							}

			}





