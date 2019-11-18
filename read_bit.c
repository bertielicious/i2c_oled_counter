#include "config.h"
uchar read_bit(void)
{
DQ_MODE = LOW;
DQ = LOW; // pull DQ low to start timeslot
DQ_MODE = HIGH; // then return high
__delay_us(15); // delay 15us from start of timeslot
return(DQ); // return value of DQ line   
}
//////////////////////////////////////////////////////////////////////////////
// READ_BIT - reads a bit from the one-wire bus. The delay
// required for a read is 15us, so the DELAY routine won't work.
// We put our own delay function in this routine in the form of a
// for() loop.
//