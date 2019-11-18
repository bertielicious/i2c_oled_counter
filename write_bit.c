#include "config.h"

//////////////////////////////////////////////////////////////////////////////
// WRITE_BIT - writes a bit to the one-wire bus, passed in bitval.
//
void write_bit(char bitval)
{
DQ_MODE = LOW;
DQ = LOW; // pull DQ low to start timeslot
if(bitval==1) DQ_MODE = HIGH; // return DQ high if write 1
__delay_us(104); // hold value for remainder of timeslot
DQ_MODE = HIGH;;
}// Delay provides 16us per loop, plus 24us. Therefore delay(5) = 104us
