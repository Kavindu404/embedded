#include <msp430.h>
/*
* main.c
*/

unsigned int ADC_Value = 0;
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;


    P1DIR |= BIT0 + BIT1;
    P1SEL0 |= BIT0 + BIT2 + BIT1;
    P1SEL1 |= BIT2;
    /*
     From writing to these 3 registers in a defined way, we can select primary functions and then
     select the Timer_A0 for PWM outputs.

     According to the above configuration;

     Pin        |   P1DIR.x     |   P1SEL1.x    |   P1SEL0.x    | Function

     P1.0             1               0               1             TA0.1

     P1.1             1               0               1             TA0.2 <- This has updated

     P1.2             0               1               1             A2

     Therefore, P1.0 has configured as TA0.1
     P1.1 has configured as TA0.2.
     P1.2 is configured as the ADC channel, i.e., as A2.
     ----------------------------------------------------------------------------------------*/
    //----------------------------------------------------------------------------------------

    PJDIR = 0x0F;
    P3DIR = 0xF0;
    /* Start of ADC Configurations
     * ---------------------------------------------------------------------------
    -----------
     */
    ADC10CTL0 = ADC10SHT_2 + ADC10ON;
    ADC10CTL1 = ADC10SHP + ADC10CONSEQ_0;
    ADC10CTL2 = ADC10RES;
    ADC10MCTL0 = ADC10SREF_0 + ADC10INCH_2;
    /* End of ADC Configuration
     * ---------------------------------------------------------------------------
    -----------
     */
    /*Start of Timer TA0 Configuration
     * ---------------------------------------------------------------------------
    -----------
     */
    TA0CTL = TASSEL_2 + MC_1;
    TA0CCR0 = 0x4000;
    TA0CCTL1 = OUTMOD_7;
    TA0CCTL2 = OUTMOD_7;
    /*End of Timer TA0 Configuration
     * ---------------------------------------------------------------------------
    -----------
     */
    while(1)
    {
        ADC10CTL0 |= ADC10ENC + ADC10SC;
        while(!(ADC10IFG & ADC10IFG0));
        ADC_Value = ADC10MEM0;
        if ((100 < ADC_Value) & (ADC_Value < 200))
        {
            PJOUT = 0x0E;
            P3OUT = 0x00;
            TA0CCR1 = 0x2000;
            TA0CCR2 = 0x0;
            /*
             If the value is between 100 and 200 this will execute.
             It will set the LED2, LED3, LED4 on.
             After this declaration, the PJ and P3 registers as below;(Each of them are 8-bit registers)

             PJ ->|    0    |   0   |   0   |   0   |   1   |   1   |   1   |   0   |
                     PJ.7      PJ.6    PJ.5    PJ.4    PJ.3    PJ.2    PJ.1    PJ.0

             P3 ->|    0    |   0   |   0   |   0   |   0   |   0   |   0   |   0   |
                     P3.7      P3.6    P3.5    P3.4    P3.3    P3.2    P3.1    P3.0

             TA0CCR1 is the Timer_A0 capture/compare '1' register. This is a 16-bit register.
             The value this register holds the high time (Duty Cycle) of the PWM signal in TA0.1.
             After this declaration, the 16 bit register of TA0CCR0 is as below;
             0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0

             TA0CCR2 is the Timer_A0 capture/compare '2' register. This is a 16-bit register.
             The value this register holds the high time (Duty Cycle) of the PWM signal in TA0.2.
             After this declaration, the 16 bit register of TA0CCR0 is as below;
             0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0

             */
        }
        else if ((200 < ADC_Value) & (ADC_Value < 300))
        {
            PJOUT = 0x02;
            P3OUT = 0x00;
            TA0CCR1 = 0x1200;
            TA0CCR2 = 0x0;
            /*
             If the value is between 200 and 300 this will execute.
             It will set the LED3, LED4 on.
             After this declaration, the PJ and P3 registers as below;(Each of them are 8-bit registers)

             PJ ->|    0    |   0   |   0   |   0   |   1   |   1   |   0   |   0   |
                     PJ.7      PJ.6    PJ.5    PJ.4    PJ.3    PJ.2    PJ.1    PJ.0

             P3 ->|    0    |   0   |   0   |   0   |   0   |   0   |   0   |   0   |
                     P3.7      P3.6    P3.5    P3.4    P3.3    P3.2    P3.1    P3.0

             TA0CCR1 is the Timer_A0 capture/compare '1' register. This is a 16-bit register.
             The value this register holds the high time (Duty Cycle) of the PWM signal in TA0.1.
             After this declaration, the 16 bit register of TA0CCR0 is as below;
             0 | 0 | 0 | 1 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0

             TA0CCR2 is the Timer_A0 capture/compare '2' register. This is a 16-bit register.
             The value this register holds the high time (Duty Cycle) of the PWM signal in TA0.2.
             After this declaration, the 16 bit register of TA0CCR0 is as below;
             0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0

             */
        }
        else if ((300 < ADC_Value) & (ADC_Value < 400))
        {
            PJOUT = 0x08;
            P3OUT = 0x00;
            TA0CCR1 = 0x0800;
            TA0CCR2 = 0x0;
            /*
             If the value is between 300 and 400 this will execute.
             It will set the LED4 on.
             After this declaration, the PJ and P3 registers as below;(Each of them are 8-bit registers)

             PJ ->|    0    |   0   |   0   |   0   |   1   |   0   |   0   |   0   |
                     PJ.7      PJ.6    PJ.5    PJ.4    PJ.3    PJ.2    PJ.1    PJ.0

             P3 ->|    0    |   0   |   0   |   0   |   0   |   0   |   0   |   0   |
                     P3.7      P3.6    P3.5    P3.4    P3.3    P3.2    P3.1    P3.0

             TA0CCR1 is the Timer_A0 capture/compare '1' register. This is a 16-bit register.
             The value this register holds the high time (Duty Cycle) of the PWM signal in TA0.1.
             After this declaration, the 16 bit register of TA0CCR0 is as below;
             0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0

             TA0CCR2 is the Timer_A0 capture/compare '2' register. This is a 16-bit register.
             The value this register holds the high time (Duty Cycle) of the PWM signal in TA0.2.
             After this declaration, the 16 bit register of TA0CCR0 is as below;
             0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0

             */
        }
        else if ((400 < ADC_Value) & (ADC_Value < 500))
        {
            PJOUT = 0x00;
            P3OUT = 0x00;
            TA0CCR1 = 0x0;
            TA0CCR2 = 0x0;
            /*
             If the value is between 400 and 500 this will execute.
             It will set the all LEDs off.
             After this declaration, the PJ and P3 registers as below;(Each of them are 8-bit registers)

             PJ ->|    0    |   0   |   0   |   0   |   0   |   0   |   0   |   0   |
                     PJ.7      PJ.6    PJ.5    PJ.4    PJ.3    PJ.2    PJ.1    PJ.0

             P3 ->|    0    |   0   |   0   |   0   |   0   |   0   |   0   |   0   |
                     P3.7      P3.6    P3.5    P3.4    P3.3    P3.2    P3.1    P3.0

             TA0CCR1 is the Timer_A0 capture/compare '1' register. This is a 16-bit register.
             The value this register holds the high time (Duty Cycle) of the PWM signal in TA0.1.
             After this declaration, the 16 bit register of TA0CCR0 is as below;
             0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0

             TA0CCR2 is the Timer_A0 capture/compare '2' register. This is a 16-bit register.
             The value this register holds the high time (Duty Cycle) of the PWM signal in TA0.2.
             After this declaration, the 16 bit register of TA0CCR0 is as below;
             0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0

             In this case, the motor is not rotating since both inputs to the motor driver is 0.
             */
        }
        else if ((500 < ADC_Value) & (ADC_Value < 600))
        {
            PJOUT = 0x00;
            P3OUT = 0x10;
            TA0CCR2 = 0x0800;
            TA0CCR1 = 0x0;
            /*
             If the value is between 500 and 600 this will execute.
             It will set the LED5 on.
             After this declaration, the PJ and P3 registers as below;(Each of them are 8-bit registers)

             PJ ->|    0    |   0   |   0   |   0   |   0   |   0   |   0   |   0   |
                     PJ.7      PJ.6    PJ.5    PJ.4    PJ.3    PJ.2    PJ.1    PJ.0

             P3 ->|    0    |   0   |   0   |   1   |   0   |   0   |   0   |   0   |
                     P3.7      P3.6    P3.5    P3.4    P3.3    P3.2    P3.1    P3.0

             TA0CCR1 is the Timer_A0 capture/compare '1' register. This is a 16-bit register.
             The value this register holds the high time (Duty Cycle) of the PWM signal in TA0.1.
             After this declaration, the 16 bit register of TA0CCR0 is as below;
             0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0

             TA0CCR2 is the Timer_A0 capture/compare '2' register. This is a 16-bit register.
             The value this register holds the high time (Duty Cycle) of the PWM signal in TA0.2.
             After this declaration, the 16 bit register of TA0CCR0 is as below;
             0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0

             In this case, the motor starts to rotate to the opposite direction since, TA0CCR1 is 0 and
             TA0CCR2 has a duty of 20%.
             */
        }
        else if ((600 < ADC_Value) & (ADC_Value < 700))
        {
            PJOUT = 0x00;
            P3OUT = 0x30;
            TA0CCR2 = 0x1200;
            TA0CCR1 = 0x0;
            /*
             If the value is between 600 and 700 this will execute.
             It will set the LED5, LED6 on.
             After this declaration, the PJ and P3 registers as below;(Each of them are 8-bit registers)

             PJ ->|    0    |   0   |   0   |   0   |   0   |   0   |   0   |   0   |
                     PJ.7      PJ.6    PJ.5    PJ.4    PJ.3    PJ.2    PJ.1    PJ.0

             P3 ->|    0    |   0   |   1   |   1   |   0   |   0   |   0   |   0   |
                     P3.7      P3.6    P3.5    P3.4    P3.3    P3.2    P3.1    P3.0

             TA0CCR1 is the Timer_A0 capture/compare '1' register. This is a 16-bit register.
             The value this register holds the high time (Duty Cycle) of the PWM signal in TA0.1.
             After this declaration, the 16 bit register of TA0CCR0 is as below;
             0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0

             TA0CCR2 is the Timer_A0 capture/compare '2' register. This is a 16-bit register.
             The value this register holds the high time (Duty Cycle) of the PWM signal in TA0.2.
             After this declaration, the 16 bit register of TA0CCR0 is as below;
             0 | 0 | 0 | 1 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0

             */
        }
        else if ((700 < ADC_Value) & (ADC_Value < 800))
        {
            PJOUT = 0x00;
            P3OUT = 0x70;
            TA0CCR2 = 0x2000;
            TA0CCR1 = 0x0;
            /*
             If the value is between 600 and 700 this will execute.
             It will set the LED5, LED6, LED7 on.
             After this declaration, the PJ and P3 registers as below;(Each of them are 8-bit registers)

             PJ ->|    0    |   0   |   0   |   0   |   0   |   0   |   0   |   0   |
                     PJ.7      PJ.6    PJ.5    PJ.4    PJ.3    PJ.2    PJ.1    PJ.0

             P3 ->|    0    |   1   |   1   |   1   |   0   |   0   |   0   |   0   |
                     P3.7      P3.6    P3.5    P3.4    P3.3    P3.2    P3.1    P3.0

             TA0CCR1 is the Timer_A0 capture/compare '1' register. This is a 16-bit register.
             The value this register holds the high time (Duty Cycle) of the PWM signal in TA0.1.
             After this declaration, the 16 bit register of TA0CCR0 is as below;
             0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0

             TA0CCR2 is the Timer_A0 capture/compare '2' register. This is a 16-bit register.
             The value this register holds the high time (Duty Cycle) of the PWM signal in TA0.2.
             After this declaration, the 16 bit register of TA0CCR0 is as below;
             0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0
             */
        }
        else if (800 < ADC_Value)
        {
            PJOUT = 0x00;
            P3OUT = 0xF0;
            TA0CCR2 = 0x2800;
            TA0CCR1 = 0x0;
            /*
             If the value is between 600 and 700 this will execute.
             It will set the LED5, LED6, LED7, LED8 on.
             After this declaration, the PJ and P3 registers as below;(Each of them are 8-bit registers)

             PJ ->|    0    |   0   |   0   |   0   |   0   |   0   |   0   |   0   |
                     PJ.7      PJ.6    PJ.5    PJ.4    PJ.3    PJ.2    PJ.1    PJ.0

             P3 ->|    1    |   1   |   1   |   1   |   0   |   0   |   0   |   0   |
                     P3.7      P3.6    P3.5    P3.4    P3.3    P3.2    P3.1    P3.0

             TA0CCR1 is the Timer_A0 capture/compare '1' register. This is a 16-bit register.
             The value this register holds the high time (Duty Cycle) of the PWM signal in TA0.1.
             After this declaration, the 16 bit register of TA0CCR0 is as below;
             0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0

             TA0CCR2 is the Timer_A0 capture/compare '2' register. This is a 16-bit register.
             The value this register holds the high time (Duty Cycle) of the PWM signal in TA0.2.
             After this declaration, the 16 bit register of TA0CCR0 is as below;
             0 | 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0
             */
        }
        else
        {
            PJOUT = 0x0F;
            P3OUT = 0x00;
            TA0CCR2 = 0x2800;
            TA0CCR1 = 0x0;
            /*
             If the value is between 100 and 200 this will execute.
             It will set the LED1, LED2, LED3, LED4 on.
             After this declaration, the PJ and P3 registers as below;(Each of them are 8-bit registers)

             PJ ->|    0    |   0   |   0   |   0   |   1   |   1   |   1   |   1   |
                     PJ.7      PJ.6    PJ.5    PJ.4    PJ.3    PJ.2    PJ.1    PJ.0

             P3 ->|    0    |   0   |   0   |   0   |   0   |   0   |   0   |   0   |
                     P3.7      P3.6    P3.5    P3.4    P3.3    P3.2    P3.1    P3.0

             TA0CCR1 is the Timer_A0 capture/compare '1' register. This is a 16-bit register.
             The value this register holds the high time (Duty Cycle) of the PWM signal in TA0.1.
             After this declaration, the 16 bit register of TA0CCR0 is as below;
             0 | 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0

             TA0CCR2 is the Timer_A0 capture/compare '2' register. This is a 16-bit register.
             The value this register holds the high time (Duty Cycle) of the PWM signal in TA0.2.
             After this declaration, the 16 bit register of TA0CCR0 is as below;
             0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0

             Note that in this case, this is still rotating in the first direction with 70% duty.
             */
        }
        __delay_cycles(25000);
    }
    return 0;
}
