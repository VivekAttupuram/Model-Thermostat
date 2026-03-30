#ifndef LCD_H
#define LCD_H

#include <xc.h>

typedef unsigned char LCDBYTE;  /* new type for an 8-bit unsigned value */

// Pins for LCD Control Signals
#define LCD_SCE         LATBbits.LATB12     /* SPI Chip Enable pin RB12 */
#define LCD_SCE_PIN     TRISBbits.TRISB12
#define LCD_RESET       LATBbits.LATB13     /* LCD Reset pin RB13 */
#define LCD_RESET_PIN   TRISBbits.TRISB13
#define LCD_DC          LATBbits.LATB14     /* LCD Data/Command pin RB14 */
#define LCD_DC_PIN      TRISBbits.TRISB14

// definitions for pin intput and output        
#define IN 1
#define OUT 0

// definitons for signaling high and low
#define LOW 0
#define HIGH 1

// definitions for signaling on the D/C LCD line
#define LCD_COMMAND     LOW
#define LCD_DATA     HIGH

void LCDWrite(LCDBYTE, LCDBYTE);
void LCDCharacter(char);
void LCD_Big_Character(int,int);
void LCDCharacter_Temp_Set(char[],int);
void LCD_flame();
void LCD_snowflake();
void pixelLocation(int x, int y);
void LCDclear();
void config_LCD();

#endif