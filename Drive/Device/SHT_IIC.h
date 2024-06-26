//=============================================================================
//	S E N S I R I O N	AG,	Laubisruetistr. 50, CH-8712 Staefa, Switzerland
//=============================================================================
// Project	:	SHT3x Sample Code (V1.1)
// File	:	i2c_hal.h (V1.1)
// Author	:	RFU
// Date	:	6-Mai-2015
// Controller:	STM32F100RB
// IDE	:	µVision V5.12.0.0
// Compiler	:	Armcc
// Brief	:	I2C hardware abstraction layer
//=============================================================================

#ifndef I2C_HAL_H 
#define I2C_HAL_H

//-- Includes -----------------------------------------------------------------
// #include "system.h"
#include "stm32f10x.h"
#include "SHT30.h"

//-- Enumerations -------------------------------------------------------------

//=============================================================================
void I2c_Init(void);
//=============================================================================
// Initializes the ports for I2C interface.
//-----------------------------------------------------------------------------

//=============================================================================
void I2c_StartCondition(void);
//=============================================================================
// Writes a start condition on I2C-Bus.
//-----------------------------------------------------------------------------
// remark: Timing (delay) may have to be changed for different microcontroller.
//	 	
// SDA:	| 	
//	 	
// SCL:	| 	

//=============================================================================
void I2c_StopCondition(void);
//=============================================================================
// Writes a stop condition on I2C-Bus.
//-----------------------------------------------------------------------------
// remark: Timing (delay) may have to be changed for different microcontroller.
//	 	
// SDA:	 	|
//	 	
// SCL:	 	|

//=============================================================================
etError I2c_WriteByte(u8 txByte);
//=============================================================================
// Writes a byte to I2C-Bus and checks acknowledge.
//-----------------------------------------------------------------------------
// input:	txByte	transmit byte
 

//
// return: error:	ACK_ERROR = no acknowledgment from sensor
//	NO_ERROR	= no error
//
// remark: Timing (delay) may have to be changed for different microcontroller.

//=============================================================================
etError I2c_ReadByte(u8 *rxByte, etI2cAck ack, u8 timeout); 

etError I2c_GeneralCallReset(void);

#endif
