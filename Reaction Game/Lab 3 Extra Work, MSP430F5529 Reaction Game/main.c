#include <msp430.h> 


/**
 * main.c
 */
unsigned int i=0;
unsigned int x=0;
unsigned int test=0;
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P4DIR|=BIT7;
	P1DIR|=BIT0;
	P1OUT&=~BIT0;
	P4OUT&=~BIT7;
	P2REN|=BIT1;
	P1REN|=BIT1;
	P1OUT|=BIT1;
	P2OUT|=BIT1;
	P1IE|=BIT1;
	P2IE|=BIT1;
	P1IES|=BIT1;
	P2IES|=BIT1;
	_enable_interrupt();
	for (i=25;i>1;i--)
	{
	    P1OUT^=BIT0;
	    for (x=40000;x>1;x--);
	}
	P1OUT&=~BIT0;
	for (x=5000;x>1;x--)
	{
	    for (i=100;i>1;i--);
	}
	
	test=1;
	P1OUT|=BIT0;
	return 0;
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    P1IE=0x00;
    P2IE=0x00;
    P1OUT&=~BIT0;
    if (test==1)
    {
        while(1)
        {
            P4OUT^=BIT7;
            for(i=40000;i>1;i--);
        }
    }
    else
    {
        while (1)
        {
            P1OUT^=BIT0;
            for (i=40000;i>1;i--);
        }
    }

}

#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    P1IE=0x00;
    P2IE=0x00;
    if (test==1)
    {
        while(1)
        {
            P1OUT^=BIT0;
            for(i=40000;i>1;i--);
        }
    }
    else
    {
        while (1)
        {
            P4OUT^=BIT7;
            for (i=40000;i>1;i--);
        }
    }
}
