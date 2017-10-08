#include <msp430.h> 
//Chris Iapicco
//Created: September 24th, 2017
//Last Updated: September 26th, 2017
/**
 * main.c
 */
 volatile double i;//Int for timing
int main(void)
{

  WDTCTL = WDTPW + WDTHOLD; // Stop WDT
  P1DIR |= 0x01;  //Sets P1.0 to output
  TA0CCTL0 = CCIE; //Enables TimerA0 interrupt
  TA0CCR0 = 12500; //Sets capture control register
  PM5CTL0 &= ~LOCKLPM5;//Turns off GPIO default high impedance mode
  TA0CTL = TASSEL_2 + MC_1 + TACLR;// Select SMCLK, upmode, clear TAR
  TA0CTL|(BIT6+BIT7);//Divide clock by 8
  TA0EX0|=(BIT2+BIT1+BIT0);//Divide clock by 8
  P5REN|=BIT5;//Turns on P5.5 resistor
  P5OUT|=BIT5;//Sets P5.5 resistor to pullup
  P5IE|=BIT5; //Enables interrupt on P5.5
  P5IES|=BIT5;//Sets P5.5 interrupt to falling edge
  P5IFG &= ~BIT5;//Clears P5 interrupt flag
  _enable_interrupt();//Enables interrupts
  P1OUT&=~BIT0;//Clears P1.0 output
  while(1)//Creates infinite loop
  {

  }
}

// Timer A0 interrupt service routine

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
  P1OUT ^= 0x01;// Toggle P1.0
}
//Port 5 GPIO interrupt service routine
#pragma vector=PORT5_VECTOR
__interrupt void Port_5(void)
{
    if ((P5IN&BIT5)==0x00)//Checks if button is pressed
    {
        TA0CTL|=(BIT2+BIT5);//Clear timer, set t continuous mode
        TA0CTL&=~BIT4;//Set to continuous mode
        P5IES^=BIT5;//Toggles edge select to select rising edge
        P5IFG&=~BIT5;//Clears interrupt flag
    }
    else if ((P5IN&BIT5)!=0x00)//Checks if button is depressed
    {
        i=TA0R;//Sets value of Timer A to a register
        TA0CTL|=BIT4;//Set to up mode
        TA0CTL&=~BIT5;//Set to up mode
        TA0CCR0=i;//Sets capture compare register to value just set to i
        P5IES^=BIT5;//Toggles edge select to detect falling edge
        P5IFG&=~BIT5;//Clears P5.5 interrupt edge select
    }
}
