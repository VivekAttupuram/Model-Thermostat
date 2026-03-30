#ifndef BUTTONS_H
#define BUTTONS_H

#define RIGHT_BUTTON PORTBbits.RB4
#define RIGHT_PIN TRISBbits.TRISB4

#define LEFT_BUTTON PORTAbits.RA2
#define LEFT_PIN TRISAbits.TRISA2

#define PRESSED 0 //Defining state when pressed as low
#define RELEASED 1 //Defining state when pressed as high

#define NONE 0// No buttons pressed
#define LEFT_PRESSED 1// Left pressed
#define RIGHT_PRESSED 2// Right button pressed
#define BOTH_PRESSED 3// Both buttons pressed

#define OUT 0
#define IN 1

void configure_buttons();
int check_buttons();


#endif
