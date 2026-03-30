/*
 * File:   ui.c
 * Author: attup
 *
 * Created on May 3, 2024, 9:35 AM
 */


#include "xc.h"
#include "ui.h"
#include <stdio.h>
#include <string.h>
#include "DS1631.h"
#include "rgbLED.h"
#include "lcd.h"
#include "buttons.h"
#define WAITING 1
#define CURRENT 0

//State of the system
int previous_setting=0;
//tracking temperatures
double temp;
double old_temp=72.0;
double low_temp=73.0, old_low_temp=0;
double high_temp=77.0, old_high_temp=0;
char high_temp_text[]="Set High Temp";
char low_temp_text[]="Set Low Temp";

//LCD screen sequence state
//int screen_sequence=INITIALIZING;

//tracking button pushes
int button_state;
int temp_set_mode=OFF;
int previous_temp_setting=0;
void config_ui()
{
    INTCON2bits.GIE=1;
    configure_UITimer();
    configure_CNTimer();
    configure_CNInterrupt();
//    configure_SnowTimer();
    
    
}

void __attribute__((__interrupt__, no_auto_psv)) _T3Interrupt(void)
{
    ui_call();
    UI_TIMER_FLAG_CLEAR;
}

void __attribute__ ((__interrupt__,no_auto_psv)) _CNInterrupt(void) {

    IEC1bits.CNIE = 0; //use timer interrupt to give space between first and second button press if there is a second

    CN_TIMER_ON;

    IFS1bits.CNIF = 0;  
    IEC1bits.CNIE = 1;
    
}

void __attribute__((__interrupt__, no_auto_psv)) _T2Interrupt(void)
{
    CN_TIMER_OFF;
    button_state= check_buttons(); //Check how many buttons pressed
    if(button_state==BOTH_PRESSED) //Change mode of temperature setting based on buttons pressed
    {
        if(temp_set_mode==0) //Change Mode to 1 so high temperature can be set
        {            
            temp_set_mode=1; 
            IEC0bits.T3IE = 0; //Disable timer 3 interrupt so interrupt does not activate until final double click
            IEC1bits.CNIE = 0; //turn off change interrupt so no other CN detected
            UI_TIMER_OFF;
            LCD_temp_print(high_temp); //print temperature 
            LCDCharacter_Temp_Set(high_temp_text,5); //print text
            printf("High temperature setting enabled...\n\r");
        }
        else if(temp_set_mode==1) //change mode to 2 if double click pressed while mode is 1 so low temp can be set
        {
            temp_set_mode=2;            
            IEC0bits.T3IE = 0;
            IEC1bits.CNIE = 0;
            UI_TIMER_OFF;
            LCD_temp_print(low_temp);
            LCDCharacter_Temp_Set(low_temp_text,5);
            printf("Low temperature setting enabled...\n\r");
        }
        else if(temp_set_mode==2) //change mode to 0 if double click pressed while mode is 1
        {
            temp_set_mode=0;
            previous_setting=2;
            IEC0bits.T3IE = 1; //Enable UI_TIMER_INTERRUPT so repeated print can occur
            IEC1bits.CNIE = 0;// disable timer interrupt so 
            printf("The upper temperature limit is: %.2f\n\rThe lower temperature limit is:%.2f\n\r",high_temp,low_temp);
            printf("Exiting temperature setting mode...\n\r");
            UI_TIMER_ON;
            
        }
    }  
    print_temp();
    
    CN_TIMER_FLAG_CLEAR;
    CN_TIMER_OFF;
    IFS1bits.CNIF = 0; 
    IEC1bits.CNIE = 1;
    
}




void ui_call()
{
    temp=DS1631_readTemp();  
    if((temp-old_temp)>=0.5||(old_temp-temp)>=0.5)
    {
        printf("Current temperature: %5.2f\n\r", temp);   //print to serial monitor
        old_temp=temp;
    }
    if(previous_setting==2)
    {
        LCDclear();
        previous_setting=0;
    }
    
    LCD_temp_print(temp);
    
    if (temp>high_temp) //Set LED and Image for high temperatures
    {
        rgbLED_Set(BLUE,MAX);
        LCD_snowflake(temp);
        previous_temp_setting=0;
        //LCDCharacter();    //print fire
    }
    else if (temp<low_temp) //Set LED and image for low temperatures
    {
        rgbLED_Set(RED,MAX);
        previous_temp_setting=0;
        //LCDCharacter();    //print snowflake
    }
    else //Set led for acceptable temperatures
    {
        if(previous_temp_setting==0)
        {
            LCDclear();
            previous_temp_setting=1;
        }
        rgbLED_Set(GREEN,MAX);
        
    }

}

void LCD_temp_print(double temp_print) // Print temperature string      
{
    char temp_buf[6];
    int temp_digit;  
    sprintf(temp_buf, "%.2f", temp_print); //convert float to string
   // LCDclear(); //clear LCD                                                        
    
    for(int i=0;i<strlen(temp_buf);i++) //Print temperature                        ////////
    {
        temp_digit=temp_buf[i]-'0'; //convert character to integer value
        if(temp_digit>=0)   //check if character in temp_buf is decimal point
        {
            LCD_Big_Character(temp_digit,i); //print number to LCD
        }
        else 
        { 
            LCDCharacter(temp_buf[i]); //print decimal point to LCD
        }
    }
        LCDCharacter('F'); //Unit of Fahrenheit   
}
    
void configure_UITimer() {
    UI_TIMER_OFF;
    UI_TIMER_CONFIG;
    UI_TIMER_RESET;
    UI_TIMER_PERIOD=0x47F8; //PWM_TIMER_CYCLE_TIME;
    UI_TIMER_INTERRUPT_CONFIG;
    UI_TIMER_ON;  
 }

void configure_CNTimer()
{
    CN_TIMER_OFF;       
    CN_TIMER_CONFIG;
    CN_TIMER_RESET;
    CN_TIMER_PERIOD=0xFFFF;
    CN_TIMER_INTERRUPT_CONFIG;
}

//void configure_SnowTimer()
//{
//    SNOW_TIMER_OFF;       
//    SNOW_TIMER_CONFIG;
//    SNOW_TIMER_RESET;
//    SNOW_TIMER_PERIOD = 0x9999;
//    SNOW_TIMER_INTERRUPT_CONFIG;
//}

void configure_CNInterrupt()
{
    IFS1bits.CNIF=0;
    IPC4bits.CNIP=4;
    IEC1bits.CNIE =1;
}


void print_temp()
{
    if(temp_set_mode==1) //set high_point based on left or right button press
    { 
        if(button_state==RIGHT_PRESSED) //Increase high temp if right button pressed
        {
            high_temp+=0.2;
        }
        if(button_state==LEFT_PRESSED) //Decrease high temp if left button pressed
        {
            high_temp-=0.2;
            if(high_temp<=low_temp)
                high_temp+=0.2;
        }
        LCDclear();
        LCD_temp_print(high_temp);
        LCDCharacter_Temp_Set(high_temp_text,5); 
        
    }
    
    if(temp_set_mode==2) //Set low temperature
    {        
        if(button_state==RIGHT_PRESSED)//Increase high temp if right button pressed
        {
            low_temp+=0.2;
            
            if (low_temp>=high_temp)
                low_temp-=0.2;
        }
        if(button_state==LEFT_PRESSED)//Decrease high temp if left button pressed
        {
            low_temp-=0.2;
        }
        LCD_temp_print(low_temp);
        LCDCharacter_Temp_Set(low_temp_text,5);
    }     
}

//void __attribute__((__interrupt__, no_auto_psv)) _T4Interrupt(void)
//{
//    printf("Interrupt 4");
//    SNOW_TIMER_FLAG_CLEAR;   
//    printf("INTERRUPR 4\n\n\r");
//}