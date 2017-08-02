/**
 *  ----------------------------------------------------------------------------
 *  Copyright (c) 2017, Anaren Microwave, Inc.
 *
 *  For more information on licensing, please see Anaren Microwave, Inc's
 *  end user software licensing agreement: EULA.txt.
 *
 *  ----------------------------------------------------------------------------
 *
 *  BMA250E.c - driver interface for the BMA250E 3-Axis MEMS
 *  accelerometer.
 *
 *  @version    1.0.00
 *  @date       24 Feb 2017
 *  @author     Anaren, air@anaren.com
 *
 *  assumptions
 *  ===========
 *  - The SPI driver provides the proper signaling sequences for read & write
 *    operations.
 *  - The SPI driver meets the timing requirements specified in the BMA250E
 *    datasheet.
 *
 *  file dependency
 *  ===============
 *  spi.h : defines the SPI read & write interfaces.
 *
 *  revision history
 *  ================
 *  ver 1.0.00 : 24 Feb 2017
 *  - initial release
 */

#include "BMA250E.h"
#include "../pin_mapping.h"

// -----------------------------------------------------------------------------
/**
 *  Global data
 */

// -----------------------------------------------------------------------------
/**
 *  Private interface
 */
#define EXTRACT_ACCEL(msb, lsb) ((int16_t)((lsb) | (msb) << 8) >> 6) // BMA250E is a 10 bit accelrometer.
// -----------------------------------------------------------------------------
/**
 *  Public interface
 */

void BMA250E_Init()
{
	AIR_SPI_SetCSPin(BMA250E_CSPIN);
	BMA250E_WriteReg(BMA250E_REG_ACCEL_PMU_RANGE, BMA250E_MODE_2G );
	BMA250E_WriteReg(BMA250E_REG_ACCEL_PMU_BW, 0x08);
}

void BMA250E_WriteReg(uint8_t addr, uint8_t data)
{
  uint8_t writeBytes[2];

  writeBytes[0] = addr;
  writeBytes[1] = data;
  AIR_SPI_Write(BMA250E_CSPIN, writeBytes, 2);
}

uint8_t BMA250E_ReadReg(uint8_t addr)
{
  uint8_t writeBytes[2];
  uint8_t readBytes[2];

  writeBytes[0] = addr | 0x80;  // set msb high for read operations
  writeBytes[1] = 0xFF;         // dummy byte

  AIR_SPI_Exchange(BMA250E_CSPIN, readBytes, writeBytes, 2);
  return readBytes[1];
}


uint8_t BMA250E_GetWhoAmIReg(void)
{
  return BMA250E_ReadReg(BMA250E_WHO_AM_I_REG_ADDR);
}

int16_t BMA250E_GetXaxisRaw(void)
{
  uint16_t returnData = (uint16_t)BMA250E_ReadReg(BMA250E_OUT_X_H_REG_ADDR) << 8;
  
  returnData |= BMA250E_ReadReg(BMA250E_OUT_X_L_REG_ADDR);
  
  return (int16_t)returnData >> 6; // Shifting the bits by 6 places.
}

int16_t BMA250E_GetYaxisRaw(void)
{
  uint16_t returnData = (uint16_t)BMA250E_ReadReg(BMA250E_OUT_Y_H_REG_ADDR) << 8;
  
  returnData |= BMA250E_ReadReg(BMA250E_OUT_Y_L_REG_ADDR);
   
  return (int16_t)returnData >> 6;
}

int16_t BMA250E_GetZaxisRaw(void)
{
  uint16_t returnData = (uint16_t)BMA250E_ReadReg(BMA250E_OUT_Z_H_REG_ADDR) << 8;
  
  returnData |= BMA250E_ReadReg(BMA250E_OUT_Z_L_REG_ADDR);
  
  return (int16_t)returnData >> 6;
}

float BMA250E_GetXaxis(void)
{
  return (float)BMA250E_GetXaxisRaw();
}

float BMA250E_GetYaxis(void)
{
  return (float)BMA250E_GetYaxisRaw();
}

float BMA250E_GetZaxis(void)
{
  return (float)BMA250E_GetZaxisRaw();
}
