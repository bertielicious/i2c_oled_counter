#include "config.h"
bool ow_reset(void)
{
   DQ_MODE = LOW;       // output
   DQ = LOW;            // drive DQ pin low for 480us
   __delay_us(480);
   DQ_MODE = HIGH;      // allow DQ to float high
   __delay_us(100);     // wait for presence signal
   if(DQ == LOW)
   {
       __delay_us(400);
       RA5 = HIGH;
       return TRUE;
   }
   else
   {
       RA5 = LOW;
       return FALSE;
   }
}
