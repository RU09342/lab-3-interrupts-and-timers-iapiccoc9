#include <msp430.h>
//Chris Iapicco
//Created: September 24th, 2017
//Last Updated: October 4th, 2017
int main(void)
{
  WDTCTL = WDTPW + WDTHOLD; // Stop WDT
  P1DIR |= BIT0;// P1.0 output
  TA0CCTL0 = CCIE;// CCR0 interrupt enabled
  TA0CCR0 = 60000;//Timer A0 CCR0 is 60000 cycles
  TA0CTL = TASSEL_2 + MC_1 + TACLR; // SMCLK, upmode, clear TAR

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, enable interrupts
  __no_operation();                         // For debugger
}


#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)
{
  P1OUT ^= 0x01;                            // Toggle P1.0
}
