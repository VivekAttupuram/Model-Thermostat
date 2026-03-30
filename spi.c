/*
 * File:   spi.c
 * Author: attup
 *
 * Created on May 3, 2024, 9:35 AM
 */

#include "xc.h"
#include "spi.h"
void config_spi()
{
    SPI1CON1bits.MSTEN = HIGH;    // make master
    SPI1CON1bits.PPRE = SPI_PPRE;  // 1:1 primary prescale
    SPI1CON1bits.SPRE = SPI_SPRE; // 1:1 secondary prescale
    SPI1CON1bits.MODE16 = LOW;   // 8-bit transfer mode
    SPI1CON1bits.SMP = LOW;      // sample in middle
    SPI1CON1bits.CKE = HIGH;      // Output on falling edge
    SPI1CON1bits.CKP = LOW;      // CLK idle state low
    SPI1STATbits.SPIEN = HIGH;    // enable SPI1
}
