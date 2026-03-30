#ifndef UI_H
#define UI_H

#include <xc.h>


#define UI_TIMER_ON T3CONbits.TON=1;
#define UI_TIMER_OFF T3CONbits.TON=0;
#define UI_TIMER_RESET TMR3 = 0
#define UI_TIMER_PERIOD PR3
#define UI_TIMER_CONFIG T3CONbits.TCS=0; T3CONbits.TGATE=0; T3CONbits.TCKPS= 0b00;
#define UI_TIMER_INTERRUPT_CONFIG IPC2bits.T3IP=1; IFS0bits.T3IF=0; IEC0bits.T3IE=1;
#define UI_TIMER_FLAG_CLEAR IFS0bits.T3IF=0;

void config_ui();
void ui_call();
void LCD_temp_print(double);
void print_temp();
void configure_CNInterrupt();
void configure_UITimer();
void configure_CNTimer();
void configure_SnowTimer();

#endif	/* XC_HEADER_TEMPLATE_H */

