/**
 * timestamps.c
 * 
 * a simple program to record timestamps from CPU clock into an array
 * at interrupts. after 20 timestamps, print them out, then do nothing.
 * */
#include <msp430fr5994.h>
#include "../lib/uartio.h"

#define BUF 50
#define IF 1
 
volatile int timestamps[BUF];
volatile unsigned int i = 0;

void print_timestamps(void)
{
    uartprintf("\n\n\rTIMESTAMPS:\n\n\r");
    for (unsigned int j = 0; j < 20; j++)
        uartprintf("timestamps[%u]: %u\n\r", j, timestamps[j]);
}

void clock_init(void)
{
    // set up clock
    CSCTL0_H = CSKEY_H;    // unlock CS registers
    CSCTL2 &= ~SELA_7;
    CSCTL0_H = 0;          // lock CS registers

    // set up timer:
    // capture rising edge
    // use ACLK
    // syncronous capture
    // enable capture mode
    // enable capture interrupt
    TA0CCTL2 = CM_1 | CCIS_1 | SCS | CAP | CCIE;
    // use SMCLK as clock source
    // start timer in continuous mode
    TA0CTL = TASSEL__SMCLK | MC__CONTINUOUS;
}

void main(void)
{
    // put the dog to sleep
    WDTCTL = WDTPW | WDTHOLD;
    // unlock ports
    PM5CTL0 &= ~LOCKLPM5;

    uart_init();
    clock_init();
    _enable_interrupts();
}

void __attribute__ ((interrupt(TIMER0_A1_VECTOR))) Timer0_A1_ISR(void)
{
    if (TA0IV == TAIV__TACCR2) {
        timestamps[i++] = TA0CCR2;
        if (i >= 20) {
            // print out the timestamps then just loop forever
            print_timestamps();
            while(1);
        }
    }
}
