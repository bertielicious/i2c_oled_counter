#include "config.h"
#include "write_bit.h"
void write_byte(uchar val)
{
uchar i;
uchar temp;
for (i=0; i<8; i++) // writes byte, one bit at a time
    {
        temp = val>>i; // shifts val right 'i' spaces
        temp &= 0x01; // copy that bit to temp
        write_bit(temp); // write bit in temp into
    }
__delay_us(104);
}
//////////////////////////////////////////////////////////////////////////////
// WRITE_BYTE - writes a byte to the one-wire bus.
//
