#include <msp430.h> 
//Chris Iapicco
//Created: September 24th, 2017
//Last Updated: September 26th, 2017
/**
 * main.c
 */
int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;//Turns off watchdog timer

  P1DIR |= BIT0;//Sets P1.0 to output
  P1OUT |= BIT0;//Sets P1.0 output to 1

  PM5CTL0 &= ~LOCKLPM5;//Disables GPIO default high impedance mode

  TA0CCTL0 = CCIE;// Enables capture compare interrupt for Timer A
  TA0CCR0 = 50000; //Sets capture compare register to 50000 cycles
  TA0CTL = TASSEL__SMCLK | MC__UP;   // selects SMCLK and up mode

  __bis_SR_register(LPM0_bits + GIE);// Enter LPM0 and set gloval interrupt enable
  __no_operation();                         // For debugger
}

// Timer0_A0 interrupt service routine
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR (void)
{
  P1OUT ^= BIT0;//Toggle LED
}
