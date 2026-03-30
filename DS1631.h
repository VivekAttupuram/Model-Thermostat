    #ifndef DS1631_H
    #define DS1631_H

    #include <xc.h>

    #define FCY 7370000/2
    #define FSCL 100

    #define NO_I2C_ERROR 1
    #define I2C_ERROR 0

    #define DS1631_ADDRESS 0b10010000   
    #define DS1631_CMD_ACCESS_CONFIG 0xAC
    #define DS1631_CMD_START_CONVERT 0x51
    #define DS1631_CMD_STOP_CONVERT 0x22
    #define DS1631_CMD_READ_TEMP 0XAA
    #define DS1631_CMD_ACCESS_TH 0XA1
    #define DS1631_CMD_ACCESS_TL 0XA2
    #define DS1631_CMD_SOFTWARE_POR 0X54

    void config_DS1631();
    void DS1631_startConvert();
    float DS1631_readTemp();

    #endif