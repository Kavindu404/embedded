#include <msp430.h>
/*
 main.c
*/
unsigned int ADC_Value = 0;
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer
    //Configure ADC10 - Pulse sample mode, ADC10SC trigger
    ADC10CTL0 = ADC10SHT_2 + ADC10ON; //16 ADC10CLKs, ADC ON
    ADC10CTL1 = ADC10SHP + ADC10CONSEQ_0; //software trigger to start a sample,
    //single ch/single conv
    ADC10CTL2 = ADC10RES; //10-bit conversion result
    ADC10MCTL0 = ADC10SREF_0 + ADC10INCH_1; //V(R+) = AVcc and V(R-) = AVss,
    //Select Channel A1
    P1SEL1 |= BIT1; // P1.1 is input for ADC
    P1SEL0 |= BIT1; // P1.1 is input for ADC
    PJDIR = 0x0F;
    P3DIR = 0xF0;
    while(1)
    {
        ADC10CTL0 |= ADC10ENC + ADC10SC; //Sample and Conversion start
        while(!(ADC10IFG & ADC10IFG0)); // Conversion complete ?
        ADC_Value = ADC10MEM0;
        if ((100 < ADC_Value) & (ADC_Value < 200))
        {
            PJOUT = 0x01;
            P3OUT = 0x00;
        }
        else if ((200 < ADC_Value) & (ADC_Value < 300))
        {
            PJOUT = 0x02;
            P3OUT = 0x00;
        }
        else if ((300 < ADC_Value) & (ADC_Value < 400))
        {
            PJOUT = 0x04;
            P3OUT = 0x00;
        }
        else if ((400 < ADC_Value) & (ADC_Value < 500))
        {
            PJOUT = 0x08;
            P3OUT = 0x00;
        }
        else if ((500 < ADC_Value) & (ADC_Value < 600))
        {
            PJOUT = 0x00;
            P3OUT = 0x10;
        }
        else if ((600 < ADC_Value) & (ADC_Value < 700))
        {
            PJOUT = 0x00;
            P3OUT = 0x20;
        }
        else if ((700 < ADC_Value) & (ADC_Value < 800))
        {
            PJOUT = 0x00;
            P3OUT = 0x40;
        }

        else if (800 < ADC_Value)
        {
            PJOUT = 0x00;
            P3OUT = 0x80;
        }
        else
        {
            P3OUT = 0x00;
            PJOUT = 0x00;
        }
        __delay_cycles(25000);
    }
return 0;
}
