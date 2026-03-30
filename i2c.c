/*
 * File:   i2c.c
 * Author: attup
 *
 * Created on May 2, 2024, 2:11 PM
 */


#include "xc.h"
#include "i2c.h"


void config_I2C()
{
    // Determine the Baud Rate Generator reload value
    // brg = FCY/(1000*FSCL) - FCY/1000000 - 2 = 31
    I2C2BRG = 0x1F;

    // Enable I2C
    I2C2CONbits.I2CEN = 1;
}

void startI2C2()
{
    I2C2CONbits.SEN = 1; // initialize start
    while(I2C2CONbits.SEN); // wait until start finished
}
void rstartI2C2()
{
    I2C2CONbits.RSEN=1; //initialize repeated start
    while(I2C2CONbits.RSEN); //wait until repeated start finished
    
}

BYTE putI2C2(BYTE data)
{
    I2C2TRN = data; // put data in transmit buffer
    while(I2C2STATbits.TRSTAT); // wait until transfer finished
    
    return (I2C2STATbits.ACKSTAT);
}

void stopI2C2()
{
    I2C2CONbits.PEN=1; // initiate stop, PEN=1
    while(I2C2CONbits.PEN); // wait until stop finished
}

BYTE getI2C2(BYTE ack2send)
{
    unsigned char inByte;

    while(I2C2CON &0x1F); // wait for idle condition
    I2C2CONbits.RCEN=1; // enable receive
    while(!I2C2STATbits.RBF); // wait for receive byte
    inByte = I2C2RCV; // read byte

    while(I2C2CON & 0x1F); // wait for idle
    I2C2CONbits.ACKDT = ack2send; // ACK type to send
    I2C2CONbits.ACKEN = 1; // enable ACK bit transmission
    while(I2C2CONbits.ACKEN); // wait until done

    return(inByte);
}