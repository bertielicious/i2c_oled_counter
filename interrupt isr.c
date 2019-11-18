
#include <pic16f1459.h>
#include "config.h"
#include "main.h"
#include "clear_OLED.h"
#include "OLED_write.h"

#include "set_page_address.h"
#include "set_columns.h"
#include "match_digit.h"
#include "split_time.h"
#include "PCF8583_read.h"
#include <stdio.h>

void interrupt isr (void)
{
    volatile uchar x,j;
    volatile static uchar overflow = 0;
    if(INTCONbits.TMR0IF == 1)
    {
       
        if (overflow >= 10)
        { 
            for (x = 0x02; x < 0x07; x++)   // read seconds, minutes, hours, year/ date, weekday/ month
            {
                PCF8583_read(0xa0,x);  
                split_time();               // split seconds, mins and hrs into msb and lsb
                
                match_digit(hours_msb, 0x1f, 0x2b, 0x03);
                match_digit(hours_lsb, 0x2c, 0x38, 0x03);
                
                set_columns(0x21,0x39, 0x45);
                set_page_address(0x78, 0x00, 0x04);
                ptr = &colon[0];
                for (j = 0; j < 8; j++)        
                {
                    OLED_write(OLED_ADDR, 0x40,*ptr);
                    ptr++;
                }
                match_digit(mins_msb, 0x46,0x52, 0x03);
                // set_columns(0x21, 0x5a, 0x62);
                match_digit(mins_lsb, 0x53,0x5f, 0x03);
                
             /*   set_columns(0x21,0x4a, 0x56);
                set_page_address(0x78, 0x00, 0x04);
                ptr = &colon[0];
                for (i = 0; i < 8; i++)        
                {
                    OLED_write(OLED_ADDR, 0x40,*ptr);
                    ptr++;
                }
                match_digit(secs_msb, 0x57, 0x63, 0x03); seconds not required to be displayed
                match_digit(secs_lsb, 0x64, 0x70, 0x03);*/
                
                
               /************************date display*************************/ 
                
                match_digit(mth_date_msb, 0x0f, 0x18, 0x00);        //day of month
                match_digit(mth_date_lsb, 0x19, 0x21, 0x00);
                
                match_digit(months_msb, 0x2b, 0x34, 0x00);        //month
                match_digit(months_lsb, 0x35, 0x3e, 0x00);
                
               
                match_digit(0x02,          0x47 ,0x50, 0x00);       // 20xx year
                match_digit(0x00,          0x51 ,0x59, 0x00);
                
                match_digit(year_date_msb, 0x5a, 0x63, 0x00);       //19 - 22 ( four years hence)
                match_digit(year_date_lsb, 0x64, 0x6e, 0x00); 
                
                
                /***********************temp display************************/
                
                match_digit(cel_msb,          0x2a ,0x36, 0x06);       // temp in deg C
                match_digit(cel_lsb,          0x37 ,0x43, 0x06);
            }
            overflow = 0;
        }
        overflow++;
        TMR0 = 0x00;  
        INTCONbits.TMR0IF = 0;
    }
    
}
