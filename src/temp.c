/**
 * blink.c - a simple program to blink the left LED with about a 1 sec delay
 *
 * Taylor Gamache, 2021-11-10
 * */
#include <msp430.h>
#include "../lib/uartio.h"

void temp_init(void)
{
	ADC12CTL0=CEF_1 + REFON + ADC12ON + ADC12SHT0_3 ; //1.5V ref,Ref on,64 clocks for sample
	ADC12CTL1=ADC12RES_1 + ADC12DIV_3; //temp sensor is at 10 and clock/4
}

int tempOut()
{
	int t=0;
	__delay_cycles(1000);              //wait 4 ref to settle
	ADC12CTL0 |= ADC12ENC + ADC12SC;      //enable conversion and start conversion
	while(ADC12CTL1);         //wait..i am converting..pum..pum..
	uartprintf("here\n\r");
	t=ADC12MEM9;                       //store val in t
	ADC12CTL0&=~ADC12ENC;                     //disable adc conv
	return(int) ((t * 27069L - 18169625L) >> 16); //convert and pass
}

void main(void)
{
	// put the dog to sleep
	WDTCTL = WDTPW | WDTHOLD;
	// unlock ports
	PM5CTL0 &= ~LOCKLPM5;
	uart_init();

	temp_init();

	volatile int temp = 0;

	uartprintf("starting up\n\r");

	while(1) {
		__delay_cycles(500);
		temp = tempOut();
		__delay_cycles(500);
		uartprintf("temp: %d\n", temp);
	}
}

