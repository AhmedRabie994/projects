/******************************************************************************
 *
 * Module: I2C
 *
 * File Name: I2C.h
 *
 * Description: header file for the ATmega16 I2C driver
 *
 * Author: Ahmed Rabie
 *
 *******************************************************************************/

#ifndef I2C_H_
#define I2C_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 **************************************************************************************************/

#define SCL_CLK 400000L
#define BITRATE(TWSR) ((F_CPU/SCL_CLK)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1)))))



/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
  * Description :
  * Function responsible for initialize the I2C driver.
  */
void I2C_Init();
/*
  * Description :
  * Function responsible for initiate START condition.
  */
uint8 I2C_Start(uint8 write_address);
/*
  * Description :
  * Function responsible for generate REPEATED START condition for read operation.
  */
uint8 I2C_Repeated_Start(uint8 read_address);
/*
  * Description :
  * Function responsible for write data/address on bus.
  */
uint8 I2C_Write(uint8 data);
/*
  * Description :
  *This function read data available on SDA line and
  *returns its acknowledgment to slave device
  *about data read successful and
  *also tells slave to transmit another data.
*/
uint8 I2C_Read_Ack();
/*
  * Description :
  * This function read last needed data byte available on SDA line
  * but do not returns acknowledgment of it.
  * It used to indicate slave that master don’t want next data
  * and want to stop communication.
  * */
uint8 I2C_Read_Nack();

/*
  * Description :
  * Function responsible for initiate STOP condition.
  */
void I2C_Stop();


#endif /* I2C_H_ */
