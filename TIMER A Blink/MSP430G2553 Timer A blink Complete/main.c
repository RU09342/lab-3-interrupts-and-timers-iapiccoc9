#include <msp430.h> 
//Chris Iapicco
//Created: September 24th, 2017
//Last Updated: September 24th, 2017
/**
 * main.c
 */
int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x01;                            // P1.0 output
  CCTL0 = CCIE;                             // CCR0 interrupt enabled
  CCR0 = 60000;//Timer 0 capture compare set to 60000 cycles
  TACTL = TASSEL_2 + MC_1 + TACLR;                  // SMCLK, upmode

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
  P1OUT ^= 0x01;                            // Toggle P1.0
}
