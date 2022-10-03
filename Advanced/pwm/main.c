#include "msp430fr5739.h"

void displayMessage(char*);
void main(void)
{

    WDTCTL = WDTPW + WDTHOLD;

    //-------------------------Start of PWM Settings---------------------------------------
    CSCTL1 = DCOFSEL_3;
    CSCTL2 = SELS_3;
    CSCTL3 = DIVS_3;

    P1DIR  |= BIT0;
    P1SEL0 |= BIT0;
    P1SEL1 &= ~BIT0;

    TA0CTL  |= TASSEL_2 + ID_0 + MC_1 + TACLR + TAIE;
    TA0CCR0  = 20000;
    TA0CCTL1 = OUTMOD_7;


    //-------------------------End of PWM Settings-----------------------------------------


    //-------------------------Start of UART Settings---------------------------------------

    P2SEL1 = BIT0 | BIT1;
    UCA0CTL1 = UCSSEL_2 | UCSWRST;
    UCA0BRW = 6;
    UCA0MCTLW = 0x2081;
    UCA0CTL1 &= ~UCSWRST;
    displayMessage("Please Enter the Position (1, 2 or 3):");

    //-------------------------End of UART Settings-----------------------------------------


    while(1)
    {
        while (!(UCA0IFG&UCRXIFG));
        switch(UCA0RXBUF){

            case('1'):{
                displayMessage("Servo Motor is at 0 degree position");
                TA0CCR1 = 1000;
                displayMessage("Please Enter the Position (1, 2 or 3):");
                break;
            }

            case('2'):{
                displayMessage("Servo Motor is at 90 degree position");
                TA0CCR1 = 1500;
                displayMessage("Please Enter the Position (1, 2 or 3):");
                break;
            }

            case('3'):{
                displayMessage("Servo Motor is at 180 degree position");
                TA0CCR1 = 2000;
                displayMessage("Please Enter the Position (1, 2 or 3):");
                break;
            }

            default:{
                displayMessage("Invalid input");
                displayMessage("Please Enter the Position (1, 2 or 3):");
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





