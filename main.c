#include <xc.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "i2c.h"
#include "uart.h"
#include "DS1631.h"
#include "buttons.h"
#include "lcd.h"
#include "fonts.h"
#include "rgbLED.h"
#include "spi.h"
#include "ui.h"
//////////////////////PROBLEM IS IT KEEPS CLEARING TEMPERATURE 7 TIMES WHEN SNOWFLAKE IS FALLING. TRIED TO FIX IN NORMAL V9 AND CLEAR JUST SNOWFLAKE BUT CANT SEE IT PRINTING EVEN WITH INTERRUPTS BEFORE CLEAR_SNOW FUNCTION FOR SOME REASON
int main(void)
{
    configure_UART1();
    printf("\033[H\033[J");
    printf("Beginning of Log:\r\n\n");
    printf("Initializing System:\r\n");
    printf("Configuring Hardware\r\n");
       
    //setup LCD
    
    config_LCD();
    LCDclear();
    //LCD_string("Initializing");
    
    //configure system
    config_I2C();
    config_DS1631();
    configure_buttons();
    configure_rgbLED();
        
    printf("Start Measuring Temperature\r\n");  
    DS1631_startConvert();
        
    printf("Start the UI\r\n"); 
    config_ui();

    while(1)
    {
        Idle();
    }
    return 0;
}