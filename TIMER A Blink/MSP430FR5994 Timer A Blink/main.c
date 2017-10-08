#include <msp430.h> 
//Chris Iapicco
//Created: September 24th, 2017
//Last Updated: September 24th, 2017
/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop WDT

    // Configure GPIO
    P1DIR |= BIT0;
    P1OUT |= BIT0;

    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    TA0CCTL0 = CCIE;                        // TACCR0 interrupt enabled
    TA0CCR0 = 50000;
    TA0CTL = TASSEL__SMCLK | MC__UP; // SMCLK, continuous mode

    __bis_SR_register(LPM0_bits | GIE);     // Enter LPM0 w/ interrupt
    __no_operation();                       // For debugger
}

// Timer0_A0 interrupt service routine
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR (void)
{
    P1OUT ^= BIT0;//Toggle LED
}
