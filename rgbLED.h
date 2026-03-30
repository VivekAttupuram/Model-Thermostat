#ifndef RGBLED_H
#define	RGBLED_H


#include <xc.h>

#define BLUE_LED_PIN TRISAbits.TRISA0 /* Blue LED pin */
#define BLUE_LED LATAbits.LATA0
#define GREEN_LED_PIN TRISAbits.TRISA1 /* Green LED pin */
#define GREEN_LED LATAbits.LATA1
#define RED_LED_PIN TRISBbits.TRISB1 /* Red LED pin */
#define RED_LED LATBbits.LATB1

/* LED States */
#define OFF 0
#define ON 1
#define DIM 2

/* LED Values */
#define ON 1
#define OFF 0

/* LED Colors */
#define WHITE 0
#define RED 1
#define MAGENTA 2
#define BLUE 3
#define CYAN 4
#define GREEN 5
#define YELLOW 6

/* Pin States */
#define OUT 0
#define IN 1

#define MAX 100
#define MIN 0

#define PWM_TIMER_ON T1CONbits.TON = 1
#define PWM_TIMER_OFF T1CONbits.TON = 0
#define PWM_TIMER_RESET TMR1 = 0
#define PWM_TIMER_PERIOD PR1
#define PWM_TIMER_CONFIG T1CONbits.TCS = 0; T1CONbits.TGATE = 0; T1CONbits.TCKPS = 0b00;
#define PWM_TIMER_INTERRUPT_CONFIG IPC0bits.T1IP = 5; IFS0bits.T1IF = 0; IEC0bits.T1IE = 1;
#define PWM_TIMER_FLAG_CLEAR IFS0bits.T1IF = 0

#define CN_TIMER_ON T2CONbits.TON=1;
#define CN_TIMER_OFF T2CONbits.TON=0;
#define CN_TIMER_RESET TMR2 = 0
#define CN_TIMER_PERIOD PR2
#define CN_TIMER_CONFIG T2CONbits.TCS=0; T2CONbits.TGATE=0; T2CONbits.TCKPS= 0b00;
#define CN_TIMER_INTERRUPT_CONFIG IPC1bits.T2IP=3; IFS0bits.T2IF=0; IEC0bits.T2IE=1;
#define CN_TIMER_FLAG_CLEAR IFS0bits.T2IF=0;

#define SNOW_TIMER_ON T4CONbits.TON=1;
#define SNOW_TIMER_OFF T4CONbits.TON=0;
#define SNOW_TIMER_RESET TMR4 = 0;
#define SNOW_TIMER_PERIOD PR4
#define SNOW_TIMER_CONFIG T4CONbits.TCS=0; T4CONbits.TGATE=0; T4CONbits.TCKPS= 0b00;
#define SNOW_TIMER_INTERRUPT_CONFIG IPC6bits.T4IP=6; IFS1bits.T4IF=0; IEC1bits.T4IE=1;
#define SNOW_TIMER_FLAG_CLEAR IFS1bits.T4IF=0;

#define PWM_TIMER_CYCLE_TIME 20000 //4e20 // needs to be < 65K

/* function prototypes */
void configure_rgbLED();
void rgbLED_Set(int color, int dimValue);
void rgbLED_setColor(int color);
void rgbLED_setDimValue(int dimValue);
void rgbLED_on();
void rgbLED_red();
void rgbLED_magenta();
void rgbLED_blue();
void rgbLED_cyan();
void rgbLED_green();
void rgbLED_yellow();
void rgbLED_white();
void rgbLED_off();

#endif	/* RGBLED_H */

