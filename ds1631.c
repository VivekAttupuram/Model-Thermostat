/*
 * File:   ds1631.c
 * Author: attup
 *
 * Created on May 2, 2024, 1:57 PM
 */


#include "xc.h"
#include "i2c.h"
#include "DS1631.h"


void config_DS1631()
{
    startI2C2();
    putI2C2(DS1631_ADDRESS & 0xFE);
    putI2C2(DS1631_CMD_ACCESS_CONFIG);
    putI2C2(0x0C); //configuration
    stopI2C2();
}
void DS1631_startConvert()
{
    startI2C2();
    putI2C2(DS1631_ADDRESS & 0xFE);
    putI2C2(DS1631_CMD_START_CONVERT);
    stopI2C2();
}

float DS1631_readTemp()
{
    BYTE temp_hi, temp_low;
    double temperature;
    
    startI2C2();
    putI2C2(DS1631_ADDRESS & 0xFE);
    putI2C2(DS1631_CMD_READ_TEMP);
    rstartI2C2();
    putI2C2(DS1631_ADDRESS|0x01);
    temp_hi=getI2C2(I2C_ACK);
    temp_low=getI2C2(I2C_NACK);
    stopI2C2();
    
    temperature= (double) (((((temp_hi<<8)|temp_low)/256.0)*9/5)+32);
    
    return temperature;
}
