/**
 *	----------------------------------------------------------------------------
 *	Copyright (c) 2017, Anaren Microwave, Inc.
 *
 *	For more information on licensing, please see Anaren Microwave, Inc's
 *	end user software licensing agreement: EULA.txt.
 *
 *	----------------------------------------------------------------------------
 *
 *	BMA250.c - driver interface for the BMA250 3-Axis MEMS
 *	accelerometer.
 *
 *	@version		1.0.00
 *	@date			 24 Feb 2017
 *	@author		 Anaren, air@anaren.com
 *
 *	assumptions
 *	===========
 *	- The SPI driver provides the proper signaling sequences for read & write
 *		operations.
 *	- The SPI driver meets the timing requirements specified in the BMA250
 *		datasheet.
 *
 *	file dependency
 *	===============
 *	spi.h : defines the SPI read & write interfaces.
 *
 *	revision history
 *	================
 *	ver 1.0.00 : 24 Feb 2017
 *	- initial release
 */

#include "bma250.h"
#include "../pin_mapping.h"

// -----------------------------------------------------------------------------
/**
 *	Global data
 */

// -----------------------------------------------------------------------------
/**
 *	Private interface
 */
#define EXTRACT_ACCEL(msb, lsb) ((int16_t)((lsb) | (msb) << 8) >> 6) // BMA250 is a 10 bit accelrometer.
// -----------------------------------------------------------------------------
/**
 *	Public interface
 */

void BMA250_Init()
{
	AIR_SPI_SetCSPin(AIR_BMA250_CSPIN);
	BMA250_WriteReg(BMA250_REG_ACCEL_PMU_RANGE, AIR_BMA250_PMU_RANGE);
	BMA250_WriteReg(BMA250_REG_ACCEL_PMU_BW, 0x08);
}

void BMA250_WriteReg(uint8_t addr, uint8_t data)
{
	uint8_t writeBytes[2];

	writeBytes[0] = addr;
	writeBytes[1] = data;
	AIR_SPI_Write(AIR_BMA250_CSPIN, writeBytes, 2);
}

uint8_t BMA250_ReadReg(uint8_t addr)
{
	uint8_t writeBytes[2];
	uint8_t readBytes[2];

	writeBytes[0] = addr | 0x80;	// set msb high for read operations
	writeBytes[1] = 0xFF;				 // dummy byte

	AIR_SPI_Exchange(AIR_BMA250_CSPIN, readBytes, writeBytes, 2);
	return readBytes[1];
}


uint8_t BMA250_GetWhoAmIReg(void)
{
	return BMA250_ReadReg(BMA250_WHO_AM_I_REG_ADDR);
}

int16_t BMA250_GetXaxisRaw(void)
{
	uint16_t returnData = (uint16_t)BMA250_ReadReg(BMA250_OUT_X_H_REG_ADDR) << 8;
	
	returnData |= BMA250_ReadReg(BMA250_OUT_X_L_REG_ADDR);
	
	return (int16_t)returnData >> 6; // Shifting the bits by 6 places.
}

int16_t BMA250_GetYaxisRaw(void)
{
	uint16_t returnData = (uint16_t)BMA250_ReadReg(BMA250_OUT_Y_H_REG_ADDR) << 8;
	
	returnData |= BMA250_ReadReg(BMA250_OUT_Y_L_REG_ADDR);
	 
	return (int16_t)returnData >> 6;
}

int16_t BMA250_GetZaxisRaw(void)
{
	uint16_t returnData = (uint16_t)BMA250_ReadReg(BMA250_OUT_Z_H_REG_ADDR) << 8;
	
	returnData |= BMA250_ReadReg(BMA250_OUT_Z_L_REG_ADDR);
	
	return (int16_t)returnData >> 6;
}

BMA250_accel_mode_t BMA250_GetPMURange()
{
	uint8_t data = BMA250_ReadReg(BMA250_REG_ACCEL_PMU_RANGE);
	
	return (BMA250_accel_mode_t)data;
	
}

float BMA250_GetXaxis(void)
{
	return (float)BMA250_GetXaxisRaw();
}

float BMA250_GetYaxis(void)
{
	return (float)BMA250_GetYaxisRaw();
}

float BMA250_GetZaxis(void)
{
	return (float)BMA250_GetZaxisRaw();
}
