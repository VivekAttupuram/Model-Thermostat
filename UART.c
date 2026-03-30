/*
 * File:   UART.c
 * Author: attup
 *
 * Created on May 2, 2024, 1:55 PM
 */

#include "xc.h"
#include "uart.h"

void configure_UART1(void) {
    RPINR18bits.U1RXR = 42;     // map UART1 RX to remappable pin RP42 (pin 21)
    RPOR4bits.RP43R = 1;        // map UART1 TX to remappable pin RP43 (pin 22)        

    // Calculate the Baud Rate generator value
    int brg = (FCY/BAUDRATE/4)-1;
    U1MODEbits.BRGH = 1;        // High speed mode
    U1BRG = brg;                 // store the value in the register
    
    U1MODEbits.PDSEL = 0;       // 8 bit data, no parity
    U1MODEbits.STSEL = 0;       // 1 stop bit
    
    U1MODEbits.UEN = 0b00;      // UxTX and UxRX pins are enabled and used; no flow control pins
    U1MODEbits.UARTEN = 1;      // enable UART RX/TX
    U1STAbits.UTXEN = 1;        //Enable the transmitter    
}

void putch(char c)
{
    while(U1STAbits.UTXBF);
    U1TXREG=c;
}