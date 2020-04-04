 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: LCD.h
 *
 * Description: Header file for the LCD driver
 *
 * Author: Ahmed Rabie
 *
 *******************************************************************************/

#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"


/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
/* LCD Data bits mode configuration */
#define DATA_BITS_MODE 4

#if (DATA_BITS_MODE==4)
#define LCD_DIR DDRA
#define LCD_PORT PORTA
/* LCD HW Pins */
#define RS 0
#define RW 1
#define EN 2

#elif (DATA_BITS_MODE == 8)
/* LCD HW Pins */
#define RS 0
#define RW 1
#define EN 2
#define LCD_DIR DDRC
#define LCD_PORT PORTC

#define LCD_DATA_PORT PORTD
#define LCD_DATA_PORT_DIR DDRD
#endif
/* LCD Commands */
#define CLEAR_COMMAND 0x01
#define FOUR_BITS_DATA_MODE 0x02
#define TWO_LINE_LCD_Four_BIT_MODE 0x28
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define SET_CURSOR_LOCATION 0x80

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
//MAIN FUNCTION
void LCD_displayCharacter(uint8 data);
/*
 * Description :
 * Function responsible for initialize the LCD driver.
 */
void LCD_init(void);

/*
 * Description :
 * Function responsible for CLEAR THE SCREEN.
 */
void LCD_clearScreen(void);
/*
 * Description :
 * Function responsible for locate the position OF THE CURSOR.
 * line 1 of lcd=row 1. ,line2 of lcd=row2
   columm 1 of lcd =columm 1., columm 16 of lcd =columm 16.
 */
void LCD_gotoRowColumn(unsigned char row,unsigned char columm);

/*
 * Description :
 * Function responsible for DISPLAY STRING.
 */
void LCD_print_str(char *text);

// SPECIAL FUNCTION

void LCD_intgerToString(int data);
void LCD_FLOATToString(double data,uint8 width,uint8 prec);

#endif /* LCD_H_ */
