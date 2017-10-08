#include <msp430.h> 
//Chris Iapicco
//Created: September 24th, 2017
//Last Updated: September 26th, 2017
/**
 * main.c
 */
 volatile double i; //Creates double register for use with Timer A
int main(void)
{

  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x01;//Sets P1.0 to output
  CCTL0 = CCIE;//Enables capture compare interrupt
  CCR0 = 12500; //Sets Capture compare to 63000 cycles
  TACTL = TASSEL_2 + MC_1; //Selects SMCLK, and up mode
  TA0CTL|=(BIT6+BIT7);//Divide clock by 8
  P1REN|=BIT3; //Enables P1.3 resistor
  P1OUT|=BIT3; //Selects pullup on P1.3
  P1IE|=BIT3; //Enables P1.3 interrupt
  P1IES|=BIT3; //Sets edge select to falling edge
  P1IFG &= ~BIT3; //Clears P1.3 interrupt flag
  _enable_interrupt(); //Enables all interrupts
  P1OUT&=~BIT0;//Sets P1.0 output to off
  while(1)//Creates infinite loop
  {

  }
}

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
  P1OUT ^= 0x01; // Toggle P1.0 LED
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    if ((P1IN&BIT3)==0x00) //Checks if button is pressed
    {
        TA0CTL|=(BIT2+BIT5);//Clear timer, set to continuous mode
        TA0CTL&=~BIT4;//Set to continuous mode
        P1IES^=BIT3; //Toggles edge select
        P1IFG&=~BIT3; //Clears Port 1 interrupt flag
    }
    else if ((P1IN&BIT3)!=0x00) //Checks if button is depressed
    {
        TA0CTL|=BIT4;//Set to up mode
        TA0CTL&=~BIT5;//Set to up mode
        i=TA0R; //Sets value of Timer A to register
        CCR0=i; //Sets value of i to capture compare register
        P1IES^=BIT3; //Toggles edge select
        P1IFG&=~BIT3; //Clears Port 1 interrupt flag
    }
}
