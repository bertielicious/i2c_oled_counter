/*
 * File:   main.c
 * Author: Phil Glazzard
 *
 * Created on 25 January 2019, 20:52
 */


#include <xc.h>
#include <stdbool.h>
#include "config_osc.h"
#include "setup_ports.h"
#include "config_TMR0.h"
#include "config_usart.h"
#include "i2c_start.h"
#include "i2c_write.h"
#include "i2c_stop.h"
#include "OLED_write.h"
#include "config_i2c.h"
#include "set_page_address.h"
#include "set_columns.h"
#include "config_OLED.h"
#include "clear_OLED.h"
#include <stdio.h>
#include "split_time.h"
#include "PCF8583_read.h"
#include "PCF8583_write.h"
#include "match_digit.h"
#include "dec_to_bcd.h"
#include "ow_reset.h"
#include "read_temperature.h"


void main(void) 
{
    uchar todays_date = 28;  // day of month
    uchar todays_month = 10;  // month
    uchar i;
    config_osc();
    setup_ports();
    config_TMR0();
    config_usart();
    config_i2c();
    config_OLED();
    __delay_ms(1);
    clear_OLED();
    __delay_ms(1);
    INTCONbits.GIE = 1;
    
    PCF8583_write(0xa0, 0x00,0x08);// mask bit set in control reg allowing direct reading of day and date
    
    dec_to_bcd(todays_date);
    PCF8583_write(0xa0, 0x05,bcd);// set mask bit in reg 0 to allow direct reading of date 
    dec_to_bcd(todays_month);
    PCF8583_write(0xa0, 0x06,bcd);// set mask bit in reg 0 to allow direct reading of month
    
    set_columns(0x21,0x44, 0x4c);       // write deg C on OLED
    set_page_address(0x78, 0x00, 0x06);
    ptr = &deg[0];
    for (i = 0; i < 8; i++)        
    {
       OLED_write(OLED_ADDR, 0x40,*ptr);
       ptr++;
    }
    set_columns(0x21,0x4d, 0x55);
    set_page_address(0x78, 0x00, 0x06);
    ptr = &C[0];
    for (i = 0; i < 8; i++)        
    {
       OLED_write(OLED_ADDR, 0x40,*ptr);
       ptr++;
    }
     
    
    while(1)
    {
       read_temperature();
       
       if(PORTAbits.RA4 == 0 && set_hrs < 23)
        {       
            __delay_ms(5);
            set_hrs = set_hrs + 1;     
            dec_to_bcd(set_hrs);
            PCF8583_write(0xa0, 0x04,bcd);
            __delay_ms(150);  
        }
      
         
       else if(PORTCbits.RC5 == 0 && set_mins < 59)
        {
            __delay_ms(5);       
            set_mins = set_mins + 1;
            dec_to_bcd(set_mins);
            PCF8583_write(0xa0, 0x03,bcd);
            __delay_ms(150);   
        }
       else if(PORTCbits.RC5 == 0 && PORTAbits.RA4 == 0)
       {
           __delay_ms(5);
           set_hrs = set_hrs - 1;
           dec_to_bcd(set_hrs);
           PCF8583_write(0xa0, 0x04,bcd);
           __delay_ms(150);  
       }
       if(set_hrs == 23 || set_mins == 59)
       {
           set_hrs = 0;
           set_mins = 0;
       }
         
    }                
}
