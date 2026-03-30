#include <xc.h>
#include "rgbLED.h"

// Keeps track of the current operation mode of theLED
int rgbLED_State = OFF;           // ON, OFF, DIM
// Keeps track of the instant value of the LED
int rgbLED_Value = OFF;           // ON, OFF
// Keeps track of the color of the LED when on
int rgbLED_Color = WHITE;       // RED, MAGENTA, BLUE, CYAN, GREEN, YELLOW, WHITE
// Keeps track of the current dimmer setting
int rgbLED_dimValue = 0;        // 0-100, 0 off, 100 on

void configure_rgbLED() {
       
    /* Configure RA0, RA1, and RB0 as output pins for LED */
    RED_LED_PIN = OUT; 
    GREEN_LED_PIN = OUT; 
    BLUE_LED_PIN = OUT; 
    
    /* Configure PWM timer */
    PWM_TIMER_OFF;
    PWM_TIMER_CONFIG;
    PWM_TIMER_RESET;
    PWM_TIMER_PERIOD = PWM_TIMER_CYCLE_TIME;
    PWM_TIMER_INTERRUPT_CONFIG;
 }

void rgbLED_Set(int color, int dimValue) {
    rgbLED_setColor(color);
    rgbLED_setDimValue(dimValue);
}

void rgbLED_setColor(int color) {
    rgbLED_Color = color;
}

void rgbLED_setDimValue(int dimValue) {
    
    // make sure dimValue in valid range
//    dimValue = (dimValue<0)?0:dimValue;
//    dimValue = (dimValue>100)?100:dimValue;
    
    // store the new dimValue 
    rgbLED_dimValue = dimValue;
    // set state based on dimValue
    if(dimValue == 0) {
        rgbLED_State = OFF;
        rgbLED_off();
        PWM_TIMER_OFF;
    } else if(dimValue == 100) {
        rgbLED_State = ON;
        rgbLED_on();
        PWM_TIMER_OFF;
    } else {
        rgbLED_State = DIM;
        if(rgbLED_Value == ON) rgbLED_on();
        PWM_TIMER_ON;
    }   
}

void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void)
{
    /* Controls the generation of the PWM waveform based on value of dimValue */
    PWM_TIMER_ON;
    if(rgbLED_Value == OFF) {
        rgbLED_on();
        PR1 = (rgbLED_dimValue)*(PWM_TIMER_CYCLE_TIME/100);
    } else {
        rgbLED_off();
        PR1 = (100-rgbLED_dimValue)*(PWM_TIMER_CYCLE_TIME/100);
    } 

    PWM_TIMER_FLAG_CLEAR;   //Clear Timer1 Interrupt flag
}

void rgbLED_on() {
    switch(rgbLED_Color) {
        case WHITE:
            rgbLED_white();
            break;
        case RED:
            rgbLED_red();
            break;
        case MAGENTA:
            rgbLED_magenta();
            break;
        case BLUE:
            rgbLED_blue();
            break;
        case CYAN:
            rgbLED_cyan();
            break;
        case GREEN:
            rgbLED_green();
            break;
        case YELLOW:
            rgbLED_yellow();
            break;
        default:
            rgbLED_off();
            break;
    }
}
void rgbLED_red() {
    rgbLED_Value = ON;
    rgbLED_Color = RED;
    if(!(rgbLED_State == DIM)) rgbLED_State = ON;
    RED_LED = ON;
    GREEN_LED = OFF;
    BLUE_LED = OFF;
}

void rgbLED_magenta() {
    rgbLED_Value = ON;
    rgbLED_Color = MAGENTA;
    if(!(rgbLED_State == DIM)) rgbLED_State = ON;
    RED_LED = ON;
    GREEN_LED = OFF;
    BLUE_LED = ON;
}

void rgbLED_blue() {
    rgbLED_Value = ON;
    rgbLED_Color = BLUE;
    if(!(rgbLED_State == DIM)) rgbLED_State = ON;
    RED_LED = OFF;
    GREEN_LED = OFF;
    BLUE_LED = ON;
}

void rgbLED_cyan() {
    rgbLED_Value = ON;
    rgbLED_Color = CYAN;
    if(!(rgbLED_State == DIM)) rgbLED_State = ON;
    RED_LED = OFF;
    GREEN_LED = ON;
    BLUE_LED = ON;
}

void rgbLED_green() {
    rgbLED_Value = ON;
    rgbLED_Color = GREEN;
    if(!(rgbLED_State == DIM)) rgbLED_State = ON;
    RED_LED = OFF;
    GREEN_LED = ON;
    BLUE_LED = OFF;
}

void rgbLED_yellow() {
    rgbLED_Value = ON;
    rgbLED_Color = YELLOW;
    if(!(rgbLED_State == DIM)) rgbLED_State = ON;
    RED_LED = ON;
    GREEN_LED = ON;
    BLUE_LED = OFF;
}

void rgbLED_white() {
    rgbLED_Value = ON;
    rgbLED_Color = WHITE;
    if(!(rgbLED_State == DIM)) rgbLED_State = ON;
    RED_LED = ON;
    GREEN_LED = ON;
    BLUE_LED = ON;
}

void rgbLED_off() {
    rgbLED_Value = OFF;
    if(!(rgbLED_State == DIM)) rgbLED_State = OFF;
    RED_LED = OFF;
    GREEN_LED = OFF;
    BLUE_LED = OFF;
}

