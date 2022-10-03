#include "msp430fr5739.h"

void displayMessage(char*);
void main(void)
{

    WDTCTL = WDTPW + WDTHOLD;
    PJDIR = 0x0F;
    P3DIR = 0xF0;
    P2SEL1 = BIT0 | BIT1;
    UCA0CTL1 = UCSSEL_2 | UCSWRST;
    UCA0BRW = 6;
    UCA0MCTLW = 0x2081;
    UCA0CTL1 &= ~UCSWRST;
    while(1)
    {
        while (!(UCA0IFG&UCRXIFG));
        switch(UCA0RXBUF){

            case('1'):{
                displayMessage("You have entered 1 LED 1 Will light-up");
                PJOUT = 0X01;
                P3OUT = 0X00;
                break;
            }

            case('2'):{
                displayMessage("You have entered 2 LED 2 Will light-up");
                PJOUT = 0X02;
                P3OUT = 0X00;
                break;
            }

            case('3'):{
                displayMessage("You have entered 3 LED 3 Will light-up");
                PJOUT = 0X04;
                P3OUT = 0X00;
                break;
            }

            case('4'):{
                displayMessage("You have entered 4 LED 4 Will light-up");
                PJOUT = 0X08;
                P3OUT = 0X00;
                break;
            }

            case('5'):{
                displayMessage("You have entered 5 LED 5 Will light-up");
                P3OUT = 0X10;
                PJOUT = 0X00;
                break;
            }

            case('6'):{
                displayMessage("You have entered 6 LED 6 Will light-up");
                P3OUT = 0X20;
                PJOUT = 0X00;
                break;
            }

            case('7'):{
                displayMessage("You have entered 7 LED 7 Will light-up");
                P3OUT = 0X40;
                PJOUT = 0X00;
                break;
            }

            case('8'):{
                displayMessage("You have entered 8 LED 8 Will light-up");
                P3OUT = 0X80;
                PJOUT = 0X00;
                break;
            }

            default:{
                displayMessage("Invalid input All LEDs will light-up");
                P3OUT =0XF0;
                PJOUT =0X0F;
                break;

            }

        }
    }

}

void displayMessage(char* msg){

    char character= *msg;
    while (character != '\0')
    {
        while (!(UCA0IFG&UCTXIFG));
        UCA0TXBUF = *msg;
        while (UCA0STATW & UCBUSY);
        msg++;
        character= *msg;
    }
    UCA0TXBUF = 0x0A;
    while (UCA0STATW & UCBUSY);
    UCA0TXBUF = 0x0D;
    while (UCA0STATW & UCBUSY);
}





