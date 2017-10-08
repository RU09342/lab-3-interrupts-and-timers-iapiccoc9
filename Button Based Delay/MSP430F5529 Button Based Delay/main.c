#include <msp430.h> 
//Chris Iapicco
//Created: September 24th, 2017
//Last Updated: October 4th, 2017
/**
 * main.c
 */
 volatile double i;//Creates a global double reg
int main(void)
{

  WDTCTL = WDTPW + WDTHOLD;//Stop WDT
  P1DIR |= 0x01;// P1.0 output
  TA0CCTL0 = CCIE;//Timer A, CCR0 interrupt enabled
  TA0CCR0 = 12500;//Sets Timer A, CCR0 to 60000 cycles
  TA0CTL = TASSEL_2 + MC_1 + TACLR;//Selects SMCLK, upmode, clear TAR
  TA0CTL|=(BIT7+BIT6);//Divides clock by 8
  P1REN|=BIT1;//Enables resistor at P1.1
  P1OUT|=BIT1;//Sets resitor to pullup at P1.1
  P1IE|=BIT1;//Enables P1.1 interrupt
  P1IES|=BIT1;//Sets edge detection to falling edge
  P1IFG &= ~BIT1;//Clears interrupt flag
  _enable_interrupt();///Enables interrupts
  P1OUT&=~BIT0;//Clears output at P1.0
  while(1)//Creates infinite loop
  {

  }
}

// Timer A0 interrupt service routine

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
  P1OUT ^= 0x01;//Toggle output at P1.0
}

//Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    if ((P1IN&BIT1)==0x00)//Checks if button is pressed
    {
        TA0CTL|=BIT5;//Change mode to continuous
        TA0CTL&=~BIT4;//Change mode to continuous
        TA0CTL|=TACLR;//Clears Timer A
        P1IES^=BIT1;//Toggles edge select to rising edge
        P1IFG&=~BIT1;//Clears P1 flag
    }
    else if ((P1IN&BIT1)!=0x00)//Checks if the button is depressed
    {
        i=TA0R;//Sets current value of Timer A to a double reg
        if (i<64000) TA0CCR0=i;//Sets Timer A, CCR0 to i
        else TA0CCR0=64000;
        P1IES^=BIT1;//Toggles edge detect to falling edge
        P1IFG&=~BIT1;//Clears P1 interrupt flag
        TA0CTL|=BIT4;//Change mode to up
        TA0CTL&=~BIT5;//Change mode to up
    }
}
