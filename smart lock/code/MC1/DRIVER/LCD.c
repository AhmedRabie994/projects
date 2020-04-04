 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: LCD.c
 *
 * Description: Source file for the LCD driver
 *
  * Author: Ahmed Rabie
 *
 *******************************************************************************/
#include "LCD.h"


/*******************************************************************************
 *                      Functions Prototypes(Private)                          *
 *******************************************************************************/
void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 data);

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void LCD_init(void)
{
#if (DATA_BITS_MODE == 4)
	LCD_DIR|=0xFF;
	LCD_PORT&=~(1<<EN);
		_delay_us(2000);
		LCD_sendCommand(FOUR_BITS_DATA_MODE);
		_delay_us(100);
		LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE);
#elif (DATA_BITS_MODE == 8)
		LCD_DIR|=(1<<EN)|(1<<RS)|(1<<RW); /* Configure the control pins(E,RS,RW) as output pins */
		LCD_DATA_PORT_DIR = 0xFF; /* Configure the data port as output port */
		LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE); /* use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode */
#endif

	LCD_sendCommand(CURSOR_OFF); /* cursor off */
	LCD_sendCommand(CLEAR_COMMAND); /* clear LCD at the beginning */
	}
void LCD_sendCommand(uint8 command){
	CLEAR_BIT(LCD_PORT,RS); /* Instruction Mode RS=0 */
	CLEAR_BIT(LCD_PORT,RW); /* write data to LCD so RW=0 */
		_delay_ms(1); /* delay for processing Tas = 50ns */
		SET_BIT(LCD_PORT,EN); /* Enable LCD E=1 */
		_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */
#if (DATA_BITS_MODE == 4)
		LCD_PORT = (LCD_PORT & 0x0F) | (command & 0xF0);
		_delay_ms(1); /* delay for processing Tdsw = 100ns */
			CLEAR_BIT(LCD_PORT,EN); /* disable LCD E=0 */
			_delay_ms(1); /* delay for processing Th = 13ns */
			SET_BIT(LCD_PORT,EN); /* Enable LCD E=1 */
			_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */
			LCD_PORT = (LCD_PORT & 0x0F) | ((command & 0x0F) << 4);
			_delay_ms(1); /* delay for processing Tdsw = 100ns */
				CLEAR_BIT(LCD_PORT,EN); /* disable LCD E=0 */
				_delay_ms(1); /* delay for processing Th = 13ns */
#elif (DATA_BITS_MODE == 8)
	LCD_DATA_PORT = command; /* out the required command to the data bus D0 --> D7 */
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_PORT,EN); /* disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
#endif
}
void LCD_displayCharacter(uint8 data){
	SET_BIT(LCD_PORT,RS); /* Data Mode RS=1 */
		CLEAR_BIT(LCD_PORT,RW); /* write data to LCD so RW=0 */
			_delay_ms(1); /* delay for processing Tas = 50ns */
			SET_BIT(LCD_PORT,EN); /* Enable LCD E=1 */
			_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */
	#if (DATA_BITS_MODE == 4)
			LCD_PORT = (LCD_PORT & 0x0F) | (data & 0xF0);
			_delay_ms(1); /* delay for processing Tdsw = 100ns */
				CLEAR_BIT(LCD_PORT,EN); /* disable LCD E=0 */
				_delay_ms(1); /* delay for processing Th = 13ns */
				SET_BIT(LCD_PORT,EN); /* Enable LCD E=1 */
				_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */
				LCD_PORT = (LCD_PORT & 0x0F) | ((data & 0x0F) << 4);
				_delay_ms(1); /* delay for processing Tdsw = 100ns */
					CLEAR_BIT(LCD_PORT,EN); /* disable LCD E=0 */
					_delay_ms(1); /* delay for processing Th = 13ns */
	#elif (DATA_BITS_MODE == 8)
		LCD_DATA_PORT = data; /* out the required command to the data bus D0 --> D7 */
		_delay_ms(1); /* delay for processing Tdsw = 100ns */
		CLEAR_BIT(LCD_PORT,EN); /* disable LCD E=0 */
		_delay_ms(1); /* delay for processing Th = 13ns */
	#endif
}
void LCD_gotoRowColumn(unsigned char row,unsigned char col){
	unsigned char fristcharadr[]={0x80,0xC0,0x90,0xD0};  // location of the rows in lcd (2lines and 4lines)
	LCD_sendCommand(fristcharadr[row-1]+(col-1));
	_delay_us(100);
	}
void LCD_print_str(char *text){
	while((*text) !='\0'){
		LCD_displayCharacter(*text);
		text++;
	}

}
void LCD_intgerToString(int data)
{
   char buff[16]; /* String to hold the ascii result */
   itoa(data,buff,10); /* 10 for decimal */
   LCD_print_str(buff);
}
void LCD_FLOATToString(double data,uint8 width,uint8 prec){
	char num[16];
	dtostrf(data,width,prec,num);
	LCD_print_str(num);
}
void LCD_clearScreen(void){
	LCD_sendCommand(CLEAR_COMMAND); //clear display
}
