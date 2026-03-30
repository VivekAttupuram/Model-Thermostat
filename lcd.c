/*
 * File:   lcd.c
 * Author: attup
 *
 * Created on May 3, 2024, 9:35 AM
 */


#include "xc.h"
#include "lcd.h"
#include "spi.h"
#include "fonts.h"
#include <stdio.h>          /* includes basic IO definitions */
#include <stdlib.h>         /* includes basic C utility function definitions */
#include <stdint.h>         /* Includes uint16_t definition */
#include <stdbool.h>        /* Includes true/false definition */
#include "rgbLED.h"

// writes one byte of data to the LCD panel
void LCDWrite(LCDBYTE dc, LCDBYTE data) {
    LCD_SCE = LOW;    // Selection LCD panel
    LCD_DC = dc;      // Indicate Data/Command signal
    SPI1BUF = data;   // Put data in output buffer for SPI1
    while(!SPI1STATbits.SPIRBF){} // wait for it to send
    Nop();            // A little extra wait time
    LCD_SCE = HIGH;   // Deselect LCD panel
       
}

// Draws one 8x5 character using the font table on LCD panel with a blank column before and after character
void LCDCharacter(char character)
{
    
    int index;
    LCDWrite(LCD_DATA, 0x00);
    if(character=='F')
    {
        pixelLocation(70,1);
        for(index=0;index<5;index++)
        {
            LCDWrite(LCD_DATA, ASCII[character - 0x20][index]); 
        }
    }
    else
    {
    for (index = 0; index < 5; index++) {
        LCDWrite(LCD_DATA, ASCII[character - 0x20][index]);
    }
    }
    LCDWrite(LCD_DATA, 0x00);
}

void LCDCharacter_Temp_Set(char character[],int y_loc)
{
    int index;
    LCDWrite(LCD_DATA, 0x00);
    pixelLocation(0,y_loc);
    for(int i=0; i<strlen(character);i++)
    {
        for (index = 0; index < 5; index++) {
            LCDWrite(LCD_DATA, ASCII[character[i] - 0x20][index]);
        }
        LCDWrite(LCD_DATA, 0x00);
    }
}

void pixelLocation(int x, int y)
{
    LCDWrite(LCD_COMMAND, 0x80|x);
    LCDWrite(LCD_COMMAND, 0x40|y);
}

void LCD_Big_Character(int character,int count)
{  
    int row,col;
    if (count>=3)
        count--;
    pixelLocation((count*18),0);
    for (row = 0; row < 3; row++) 
    {
        pixelLocation((count*18),row+1);                // Blank column before digit
        for (col = 0; col < 13; col++) {
            LCDWrite(LCD_DATA, BIGNUM[character][row][col]);
        }
        //pixelLocation(count*18,row+1);
    }
}

void LCD_snowflake(double temp_snow)
{  
    int row,col;
    pixelLocation(70,3);
    for (row = 0; row < 2; row++) 
    {      
        pixelLocation(70,row+3);
        for (col = 0; col < 14; col++) {
            LCDWrite(LCD_DATA, SNOW[row][col]);
        }
    }
    LCDCharacter_Temp_Set("Cooling",5);
}

// Clears the LCD panel and puts cursor in the top left corner of screen
void LCDclear(void){
    int i;
    for (i=0;i<6*84;i++){
        LCDWrite(LCD_DATA,0x00);
    }
    LCDWrite(LCD_COMMAND,0x40);
    LCDWrite(LCD_COMMAND,0x80);
}

void config_LCD()
{
    // setup SPI pins
    LCD_SCE_PIN = OUT;
    LCD_RESET_PIN = OUT;
    LCD_DC_PIN = OUT;

    config_spi();
    
    // reset LCD panel to get it into a known state
    LCD_RESET = LOW;
    LCD_RESET = HIGH;
        // send commands to LCD panel to configure it
    LCDWrite(LCD_COMMAND, 0x21);  // LCD Extended Commands.
    LCDWrite(LCD_COMMAND, 0x80 );  // Set LCD Vop (Contrast), valid values of 0x80 - 0xFF, section 8.9 of data sheet. 
    LCDWrite(LCD_COMMAND, 0x04 );  // Set Temp coefficent, valid values are 0x04 - 0x07, typcally set to 0x04, section 8.7 and page 19 of data sheet
    LCDWrite(LCD_COMMAND, 0x13 );  // LCD bias mode, values values are 0x10 - 0x17, typically set to 0x13, 1:48, section 8.8 and Table 4 of data sheet
    LCDWrite(LCD_COMMAND, 0x20 );  // LCD Basic Commands
    LCDWrite(LCD_COMMAND, 0x0C );  // LCD in normal mode.
  
    // Draw the message on the LCD screen
    LCDclear();
}