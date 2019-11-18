#include "config.h"
#include "ow_reset.h"
#include "write_byte.h"
#include "read_byte.h"
#include <stdio.h>
void read_temperature (void)
{
int bytes1and2 = 0;
uchar w;
uchar byte1, byte2 = 0;
char get[10];
char temp_lsb,temp_msb;
int k;
char temp_f,temp_c;
ow_reset();
write_byte(0xcc);   // skip ROM
write_byte(0x4e);   // write to scratch pad configuration register
for (w = 0; w < 3; w++)
{
    write_byte(0x00); // 9 bit resolution   
}
__delay_us(104);

ow_reset();
write_byte(0xCC); //Skip ROM
write_byte(0x44); // Start Conversion
__delay_ms(95);     // wait for the time taken to convert a 9 bit temperature
ow_reset();
write_byte(0xCC); // Skip ROM
write_byte(0xBE); // Read Scratch Pad

byte1 = read_byte();    // read first temperature byte (LSB))
byte2 = read_byte();    // read second temperature byte (MSB))
bytes1and2= (byte2<<8 | byte1) ; // combine bytes by shifting byte2 into a 16 bit data
celcius = bytes1and2/16;
}