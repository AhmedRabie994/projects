/******************************************************************************
 *
 * Module: UART
 *
 * File Name: UART.h
 *
 * Description: header file for the ATmega16 UART driver
 *
 * Author: Ahmed Rabie
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"


/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* UART Driver Baud Rate */
#define USART_BAUDRATE 9600


/*******************************************************************************
  *                      Functions Prototypes                                   *
  *******************************************************************************/

 /*
  * Description :
  * Function responsible for initialize the UART driver.
  */
 void UART_init(void);

 /*
   * Description :
   * Function responsible for send one byte .
   */
 void UART_sendByte(const uint8 data);

 /*
    * Description :
    * Function responsible for receive one byte .
    */

 uint8 UART_recieveByte(void);


 /*
     * Description :
     * Function responsible for send string .
     */

 void UART_sendString(const uint8 *Str);

 /*
      * Description :
      * Function responsible for receive string .
      */
 void UART_receiveString(uint8 *Str); // Receive until #





#endif /* UART_H_ */
