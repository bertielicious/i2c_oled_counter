#include "config.h"
#include "read_bit.h"
uchar read_byte(void)
{
uchar i;
uchar value = 0;
for (i=0;i<8;i++)
    {
        if(read_bit()) value|=0x01<<i;  // reads byte in, one byte at a time and then
                                        // shifts it left
        __delay_us(120);                // wait for rest of timeslot
    }
return(value);
}