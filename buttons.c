/*
 * File:   buttons.c
 * Author: Vivek Attupuram
 *
 * Created on April 11, 2024
 */
#include "xc.h"
#include "Buttons.h"
#include "ui.h"
void configure_buttons()
{
    RIGHT_PIN= IN;
    LEFT_PIN= IN;
    CNENAbits.CNIEA2=1; //Enable CN for pin 4A2
    CNENBbits.CNIEB4=1; //Enable CN for pin RB4
   // CNPUAbits.CNPUA2=1; //Enable PU resistor for pin RA2
   // CNPUBbits.CNPUB4=1; //Enable PU resistor for pin RB4
}


int check_buttons()
{   
   
    if(LEFT_BUTTON==RELEASED&&RIGHT_BUTTON==RELEASED){
        return NONE;
    }
    else if(LEFT_BUTTON==PRESSED&&RIGHT_BUTTON==RELEASED){
        return LEFT_PRESSED;   
    }
    else if(LEFT_BUTTON==RELEASED&&RIGHT_BUTTON==PRESSED){
        return RIGHT_PRESSED;
    }
    else
        return BOTH_PRESSED;
}