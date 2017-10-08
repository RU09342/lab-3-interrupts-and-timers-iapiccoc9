#include <msp430.h> 
//Chris Iapicco
//Created: September 24th, 2017
//Last Updated: September 24th, 2017
/**
 * main.c
 */
 volatile double i;
int main(void)
{

  WDTCTL = WDTPW + WDTHOLD;//Disables the watchdog timer
  P1DIR |= 0x01;//Sets P1.0 to output
  PM5CTL0 &= ~LOCKLPM5;//Shuts off GPIO default high impedance mode
  TB0CTL|=(BIT7+BIT6);//Divide timer by 8
  TB0CCTL0 |= CCIE;//Enables Timer B CCR0 interrupt enable
  TB0CCR0 = 12500;//Sets Timer B CCRO to 50000 cycles
  TB0CTL |= TBSSEL__SMCLK | MC__UP;//Selects SMCLK, up mode
  P1REN|=BIT1;//Enables Resistor at P1.1
  P1OUT|=BIT1;//Sets P1.1 resistor to pullup
  P1IE|=BIT1;//Enables P1.1 interrupt
  P1IES|=BIT1;//Sets P1.1 interrupt to falling edge
  P1IFG &= ~BIT1;//Clears P1.1 interrupt flag
  _enable_interrupt();//Enables interrupts
  P1OUT&=~BIT0;//Sets P1.0 output to 0
  while(1)//Creates infinite loop
  {

  }
}

// Timer B0 interrupt service routine

#pragma vector=TIMER0_B0_VECTOR
__interrupt void Timer_B (void)
{
  P1OUT ^= 0x01;//Toggles output at P1.0
}
//Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    if ((P1IN&BIT1)==0x00)//Checks if button is pressed
    {
        TB0CTL|=(BIT5+BIT2);//Clear timer, set to continuous mode
        TB0CTL&=~BIT4;//Set timer to continuous mode
        P1IES^=BIT1;//Toggles edge detect to rising edge
        P1IFG&=~BIT1;//Clears P1 interrupt flag
    }
    else if ((P1IN&BIT1)!=0x00)//Checks in button is depressed
    {
        TB0CTL|=BIT4;//Set to up mode
        TB0CTL&=~BIT5;//Set to up mode
        i=TB0R;//Sets current value of Timer B to a double reg
        TB0CCR0=i;//Sets Timer B0 CCRO to i
        P1IES^=BIT1;//Toggles edge detect to rising egde
        P1IFG&=~BIT1;//Clears P1 interrupt flag
    }
}
