#include <msp430.h>

#define COUNTER_VALUE 1250
#define BUF 50

volatile int timestamps[BUF];
volatile unsigned int i = 0;

void clock_init(void)
{
	// set up clock
    CSCTL0_H = CSKEY_H;
	CSCTL2 |= SELA__VLOCLK;
	CSCTL0_H = 0;
	
	// set up timer
    TA0CCR0 = COUNTER_VALUE;
    TA0CTL  = TASSEL__ACLK + MC__UP + ID__8;;
	TA0CCTL0 = CAP | CCIE;
    TA0CTL |= TAIE;
}

void main(void)
{
	// put the dog to sleep
	WDTCTL = WDTPW | WDTHOLD;
	// unlock ports
	PM5CTL0 &= ~LOCKLPM5;
	
	// set LEDs as output + start with them off
	P1DIR |= 0x3;
	P1OUT &= ~0x3;

	clock_init();

	_enable_interrupts();

	while(1) {
		_BIS_SR(LPM3_bits + GIE);
		// light up right LED if timer info is recorded
		if (timestamps[0]) P1OUT |= BIT1;
		else P1OUT &= ~BIT1;
	}
}

void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) Timer_A(void)
{
	// light up left LED if in interrupt
	P1OUT |= BIT0;
	// whenever interrupt if triggered, copy timestamp to timestamp[i]
	timestamps[i++] = TA0CCR0;
	TA0CTL |= TACLR;
}
