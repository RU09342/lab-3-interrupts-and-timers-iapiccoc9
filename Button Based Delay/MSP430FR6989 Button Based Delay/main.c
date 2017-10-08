#include <msp430.h> 
//Chris Iapicco
//Created: September 24th, 2017
//Last Updated: September 24th, 2017
/**
 * main.c
 */
 volatile double i;//Creates double register for use with Timer A
int main(void)
{

  WDTCTL = WDTPW + WDTHOLD;// Stops the WDT
  P1DIR |= 0x01;//Sets P1.0 to output
  TA0CCTL0 = CCIE;//Enables Capture compare interrupt for Timer A
  TA0CCR0 = 12500;//Sets capture compare register to 60000 cycles
  PM5CTL0 &= ~LOCKLPM5;//Disables GPIO default high impedance mode
  TA0CTL = TASSEL_2 + MC_1 + TACLR;//Selects SMCLK, upmode, clear TAR
  TA0CTL|=(BIT7+BIT6);//Divide timer by 8
  P1REN|=BIT1;//Enables resistor on PORT1.1
  P1OUT|=BIT1;//Selects pullup for PORT 1.1
  P1IE|=BIT1;//Enables interrupts for P1.1
  P1IES|=BIT1;//Selects falling edge detection
  P1IFG &= ~BIT1;//Clears 1.1 interrupt flag
  _enable_interrupt();//Enables interrupts
  P1OUT&=~BIT0;//Clears output for P1.0
  while(1) //Creates infinite loop
  {

  }
}

// Timer A0 interrupt service routine

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
  P1OUT ^= 0x01;//Toggle output for P1.0
}
//Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    if ((P1IN&BIT1)==0x00)//Checks if button is pressed
    {
        TA0CTL|=(BIT2+BIT5);//Set to continuous mode, clear timer
        TA0CTL&=~BIT4;//Set to continuous mode
        P1IES^=BIT1;//Toggles edge detect for rising edge
        P1IFG&=~BIT1;//Clears interrupt flag for P1.1
    }
    else if ((P1IN&BIT1)!=0x00)//Checks if button is depressed
    {
        TA0CTL&=~BIT5;//Set to up mode
        TA0CTL|=BIT4;//Set to up mode
        i=TA0R;//Sets current value of Timer A to a register
        TA0CCR0=i;//Sets value in i to capture compare register
        P1IES^=BIT1;//Toggles edge detection to falling edge
        P1IFG&=~BIT1;//Clears P1.1 interrupt flag
    }
}
