/***************************************************
  This is a library for the L3GD20 GYROSCOPE

  Designed specifically to work with the Adafruit L3GD20 Breakout 
  ----> https://www.adafruit.com/products/1032

  These sensors use I2C or SPI to communicate, 2 pins (I2C) 
  or 4 pins (SPI) are required to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Kevin "KTOWN" Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/
#ifndef __L3GD20_H__
#define __L3GD20_H__

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Adafruit_Sensor.h>
#include <Wire.h>

/*=========================================================================
    I2C ADDRESS/BITS AND SETTINGS
    -----------------------------------------------------------------------*/
    #define L3GD20_ADDRESS           (0x6B)        // 1101011
    #define L3GD20_POLL_TIMEOUT      (100)         // Maximum number of read attempts
    #define L3GD20_ID                (0b11010100)
    #define GYRO_SENSITIVITY_250DPS  (0.00875F)    // Roughly 22/256 for fixed point match
    #define GYRO_SENSITIVITY_500DPS  (0.0175F)     // Roughly 45/256
    #define GYRO_SENSITIVITY_2000DPS (0.070F)      // Roughly 18/256
/*=========================================================================*/

/*=========================================================================
    REGISTERS
    -----------------------------------------------------------------------*/
    typedef enum
    {                                             // DEFAULT    TYPE
      GYRO_REGISTER_WHO_AM_I            = 0x0F,   // 11010100   r
      GYRO_REGISTER_CTRL_REG1           = 0x20,   // 00000111   rw
      GYRO_REGISTER_CTRL_REG2           = 0x21,   // 00000000   rw
      GYRO_REGISTER_CTRL_REG3           = 0x22,   // 00000000   rw
      GYRO_REGISTER_CTRL_REG4           = 0x23,   // 00000000   rw
      GYRO_REGISTER_CTRL_REG5           = 0x24,   // 00000000   rw
      GYRO_REGISTER_REFERENCE           = 0x25,   // 00000000   rw
      GYRO_REGISTER_OUT_TEMP            = 0x26,   //            r
      GYRO_REGISTER_STATUS_REG          = 0x27,   //            r
      GYRO_REGISTER_OUT_X_L             = 0x28,   //            r
      GYRO_REGISTER_OUT_X_H             = 0x29,   //            r
      GYRO_REGISTER_OUT_Y_L             = 0x2A,   //            r
      GYRO_REGISTER_OUT_Y_H             = 0x2B,   //            r
      GYRO_REGISTER_OUT_Z_L             = 0x2C,   //            r
      GYRO_REGISTER_OUT_Z_H             = 0x2D,   //            r
      GYRO_REGISTER_FIFO_CTRL_REG       = 0x2E,   // 00000000   rw
      GYRO_REGISTER_FIFO_SRC_REG        = 0x2F,   //            r
      GYRO_REGISTER_INT1_CFG            = 0x30,   // 00000000   rw
      GYRO_REGISTER_INT1_SRC            = 0x31,   //            r
      GYRO_REGISTER_TSH_XH              = 0x32,   // 00000000   rw
      GYRO_REGISTER_TSH_XL              = 0x33,   // 00000000   rw
      GYRO_REGISTER_TSH_YH              = 0x34,   // 00000000   rw
      GYRO_REGISTER_TSH_YL              = 0x35,   // 00000000   rw
      GYRO_REGISTER_TSH_ZH              = 0x36,   // 00000000   rw
      GYRO_REGISTER_TSH_ZL              = 0x37,   // 00000000   rw
      GYRO_REGISTER_INT1_DURATION       = 0x38    // 00000000   rw
    } gyroRegisters_t;    
/*=========================================================================*/

/*=========================================================================
    DATA RATE & BANDWIDTH
    -----------------------------------------------------------------------*/
    typedef enum
    {
	  GYRO_SPEED_95_12_5_HZ				= 0x00, 	// 95 Hz update rate, 12.5 Hz bandwidth
	  GYRO_SPEED_95_25_HZ				= 0x01, 	// 95 Hz update rate, 25 Hz bandwidth
	  GYRO_SPEED_95_25_HZ1				= 0x02, 	// 95 Hz update rate, 25 Hz bandwidth
	  GYRO_SPEED_95_25_HZ2				= 0x03, 	// 95 Hz update rate, 25 Hz bandwidth
	  GYRO_SPEED_190_12_5_HZ			= 0x04, 	// 190 Hz update rate, 12.5 Hz bandwidth
	  GYRO_SPEED_190_25_HZ				= 0x05, 	// 190 Hz update rate, 25 Hz bandwidth
	  GYRO_SPEED_190_50_HZ				= 0x06, 	// 190 Hz update rate, 50 Hz bandwidth
	  GYRO_SPEED_190_70_HZ				= 0x07, 	// 190 Hz update rate, 70 Hz bandwidth
	  GYRO_SPEED_380_20_HZ				= 0x08, 	// 380 Hz update rate, 20 Hz bandwidth
	  GYRO_SPEED_380_25_HZ				= 0x09, 	// 380 Hz update rate, 25 Hz bandwidth
	  GYRO_SPEED_380_50_HZ				= 0x0a, 	// 380 Hz update rate, 50 Hz bandwidth
	  GYRO_SPEED_380_100_HZ				= 0x0b, 	// 380 Hz update rate, 100 Hz bandwidth
	  GYRO_SPEED_760_30_HZ				= 0x0c, 	// 760 Hz update rate, 30 Hz bandwidth
	  GYRO_SPEED_760_35_HZ				= 0x0d, 	// 760 Hz update rate, 35 Hz bandwidth
	  GYRO_SPEED_760_50_HZ				= 0x0e, 	// 760 Hz update rate, 50 Hz bandwidth
	  GYRO_SPEED_760_100_HZ				= 0x0f	 	// 760 Hz update rate, 100 Hz bandwidth
	} gyroSpeed_t;
/*=========================================================================*/

/*=========================================================================
    OPTIONAL SPEED SETTINGS
    -----------------------------------------------------------------------*/
    typedef enum
    {
      GYRO_RANGE_250DPS  = 250,
      GYRO_RANGE_500DPS  = 500,
      GYRO_RANGE_2000DPS = 2000
    } gyroRange_t;
/*=========================================================================*/

class Adafruit_L3GD20_Unified : public Adafruit_Sensor
{
  public:
    Adafruit_L3GD20_Unified(int32_t sensorID = -1);

    bool begin           ( gyroRange_t rng = GYRO_RANGE_250DPS );
    void enableAutoRange ( bool enabled );
    void getEvent        ( sensors_event_t* );
    void getSensor       ( sensor_t* );
	void setRegister(gyroRegisters_t reg, uint8_t val);
	uint8_t getRegister(gyroRegisters_t reg);
	void setSpeed(gyroSpeed_t speed);
	gyroSpeed_t getSpeed(void);

  private:
    void        write8  ( byte reg, byte value );
    byte        read8   ( byte reg );
    gyroRange_t _range;
    int32_t     _sensorID;
    bool        _autoRangeEnabled;
};

#endif
