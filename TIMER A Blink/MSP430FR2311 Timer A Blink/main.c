#include <msp430.h>
//Chris Iapicco
//Created: September 24th, 2017
//Last Updated: September 26th, 2017
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;//Stop WDT


    P1DIR |= BIT0;//Sets P1.0 to output
    P1OUT |= BIT0;//Sets P1.1 output to 1

    PM5CTL0 &= ~LOCKLPM5; //Disables GPIO default high impedance mode

    TB0CCTL0 |= CCIE;// Timer B, capture control 0 interrupt enable
    TB0CCR0 = 50000;//Timer B, capture control 0 set to 50000 cycles
    TB0CTL |= TBSSEL__SMCLK | MC__UP;//select SMCLK, up mode

    __bis_SR_register(LPM0_bits | GIE);// Enter LPM3 and enable interrupts
    __no_operation();                             // For debug
}

// Timer B0 interrupt service routine
#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer_B (void)
{
    P1OUT ^= BIT0;//Toggle LED @ P1.0
}
