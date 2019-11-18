
#include <pic16f1459.h>

void setup_ports(void)
{
    ANSELA = 0x00;
    ANSELB = 0x00;
    ANSELC = 0x00;  
    TRISCbits.TRISC7 = 0;   // pin 9 debug LED green
    TRISCbits.TRISC6 = 1;   // pin 8 18B20 temp sensor port 
    TRISCbits.TRISC5 = 1;   // pin 5 HOURS ++ button
    TRISAbits.TRISA5 = 0;   // pin 2 debug LED red
    TRISAbits.TRISA4 = 1;   // pin 3 minutes++ button
}
