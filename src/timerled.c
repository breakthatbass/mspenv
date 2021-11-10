/**
 * timerled1.c - a simple program to toggle both LEDs by using a timer
 * rather than a delay.
 *
 * A delay function in C is a waste of CPU resources.
 * By using a timer, it can delay while the CPU can be used for other tasks.
 * Timer are a product of the hardware.
 *
 * Taylor Gamache, 2021-11-10
 * */
#include <msp430fr5994.h>

#define CTR_VAL 500

void start_timer(void) {
	// Setup the timer
	TA0CCTL0 = CCIE;
	TA0CCR0 = CTR_VAL;
	TA0CTL = TASSEL__ACLK + MC__UP + ID__8; // ACLK, Up Mode, Prescaler = 8
	TA0CTL |= TAIE;
}

void main(void)
{
	// stop the watchdog timer
	WDTCTL = WDTPW | WDTHOLD;
	// allow changes to port registers
	PM5CTL0 &= ~LOCKLPM5;

	 // Select ACLK to use VLO clock source
	CSCTL0_H = CSKEY_H;
	CSCTL2 |= SELA__VLOCLK;
	CSCTL0_H = 0;

	// set pins for LEDs to output
	P1DIR = BIT0 | BIT1;
	// preload LED 1 on, LED 2 off
	P1OUT = ~BIT0;
	
	start_timer();

	while (1) {
		_BIS_SR(LPM3_bits + GIE);
	}
}

void __attribute__((interrupt(TIMER0_A0_VECTOR))) Timer_A(void)
{
	P1OUT ^= BIT0 | BIT1;
	// reset the timer
	TA0CTL |= TACLR;
}
