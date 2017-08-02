// Copyright (c) 2017, Anaren Inc.
// All rights reserved.
// Author : Mihir Dani
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer. 
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// The views and conclusions contained in the software and documentation are those
// of the authors and should not be interpreted as representing official policies, 
// either expressed or implied, of the FreeBSD Project.

#ifndef BMA250E_H
#define BMA250E_H

//------------------------------------------------------------------------------
/**
 *  Defines, enumerations, and structure definitions
 */

#include "pin_mapping.h"
#include "BMA250E_config.h"
#include "../spi/spi.h"
#include <stdint.h>

#ifndef bool
#define bool uint8_t
#endif

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

//------------------------------------------------------------------------------
/**
 *  Defines, enumerations, and structure definitions
 */
#define BMA250E_WHO_AM_I_REG_ADDR        0x00  // Device Identification (read only)
#define BMA250E_OUT_X_L_REG_ADDR         0x02  // Data Output X LSB (read only)
#define BMA250E_OUT_X_H_REG_ADDR         0x03  // Data Output X MSB (read only)
#define BMA250E_OUT_Y_L_REG_ADDR         0x04  // Data Output Y LSB (read only)
#define BMA250E_OUT_Y_H_REG_ADDR         0x05  // Data Output Y MSB (read only)
#define BMA250E_OUT_Z_L_REG_ADDR         0x06  // Data Output Z LSB (read only)
#define BMA250E_OUT_Z_H_REG_ADDR         0x07  // Data Output Z MSB (read only)

#define BMA250E_REG_ACCEL_PMU_RANGE 	 0x0F
#define BMA250E_REG_ACCEL_PMU_BW 		 0x10

#define BMA250E_SPI_MODE 0
#define BMA250E_MSB_FIRST 1
/**
 *  eBMA250EOperatingMode - type indicating the operating mode of the
 *  BMA250E device.  The BMA250E offers two modes; Normal and Low-power.  Refer
 *  to the BMA250E datasheet for details regarding the different modes.
 */
enum eBMA250EOperatingMode
{
  BMA250E_LowPower              = 0x00,
  BMA250E_Normal                = 0x01
};

/**
 *  eBMA250EDataRate - type indicating the output data rate of the BMA250E
 *  device, specified in Hz.
 */
enum eBMA250EDataRate
{
  BMA250E_Rate_PowerDown        = 0x00, // power down mode (default)
  BMA250E_Rate_1Hz              = 0x01, // normal & low-power modes
  BMA250E_Rate_10Hz             = 0x02, // normal & low-power modes
  BMA250E_Rate_25Hz             = 0x03, // normal & low-power modes
  BMA250E_Rate_50Hz             = 0x04, // normal & low-power modes
  BMA250E_Rate_100Hz            = 0x05, // normal & low-power modes
  BMA250E_Rate_200Hz            = 0x06, // normal & low-power modes
  BMA250E_Rate_400Hz            = 0x07, // normal & low-power modes
  BMA250E_Rate_1600Hz           = 0x08, // low-power mode only
  BMA250E_Rate_1250Hz_5000Hz    = 0x09  // 1.25kHz normal mode, 5kHz low-power mode
};

typedef enum {
	BMA250E_MODE_2G = 0x3,
	BMA250E_MODE_4G = 0x5,
	BMA250E_MODE_8G = 0x8,
	BMA250E_MODE_16G = 0xC,
} BMA250E_accel_mode_t;

void BMA250E_Init();

/**
Write an 8-bit value to a device register.  All of the BMA250E registers are
read only except for the configuration and control registers.  This function
does not do any form of error checking, so trying to write to one of the
read-only registers may result in undesireable behavior.
@param addr device register address
@param data data to be written to the specified register address
*/
void BMA250E_WriteReg(uint8_t addr, uint8_t data);

/**
Read an 8-bit value from a device register.
@param addr device register address
@return data read from the specified register address
*/
uint8_t BMA250E_ReadReg(uint8_t addr);

/**
Read WHO_AM_I identification register.
@return contents of WHO_AM_I register.  Value always = 0x33 (ascii '3').
*/
uint8_t BMA250E_GetWhoAmIReg(void);


int16_t BMA250E_GetXaxisRaw(void);
int16_t BMA250E_GetYaxisRaw(void);
int16_t BMA250E_GetZaxisRaw(void);

float BMA250E_GetXaxis(void);
float BMA250E_GetYaxis(void);
float BMA250E_GetZaxis(void);


#endif  /* BMA250E_H */
