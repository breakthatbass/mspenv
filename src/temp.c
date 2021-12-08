/**
 * temp.c
 * 
 * get the temperature and humidity using a DHT11 sensor
 * */
#include <msp430fr5994.h>
#include "../lib/uartio.h"

#define MAX 20

volatile unsigned int timestamps[MAX];
unsigned int i = 0;

void print_timestamps(void)
{
    // we got 20 timestamps, print them out then blink forever
    uartprintf("\n\n\rTIMESTAMPS:\n\n\r");
    for (unsigned int j = 0; j < MAX; j++)
        uartprintf("timestamps[%u]: %u\n\r", j, timestamps[j]);
}

void clock_init(void)
{


    // Timer0_A3 Setup
    TA0CCTL2 = CM_1 | CCIS_1 | SCS | CAP | CCIE;
                                            // Capture rising edge,
                                            // Use CCI2B=ACLK,
                                            // Synchronous capture,
                                            // Enable capture mode,
                                            // Enable capture interrupt

    TA0CTL = TASSEL__SMCLK | MC__CONTINUOUS;// Use SMCLK as clock source,
                                            // Start timer in continuous mode
}

void temp_init(void)
{
    // wait 2 seconds
    __delay_cycles(2000000);
    P5DIR |= BIT2;
    P5OUT &= ~BIT2;
    __delay_cycles(20000);
    P5OUT |= BIT2;
    __delay_cycles(20);
    // set port as input
    P5DIR &= ~BIT2;
    P5SELC |= BIT2;
}

int main(void)
{
    // put the dawg to sleep
    WDTCTL = WDTPW | WDTHOLD;

        // Clock System Setup
    CSCTL0_H = CSKEY_H;                     // Unlock CS registers
    CSCTL2 &= ~SELA_7;
    CSCTL2 |= SELA__VLOCLK;                 // Select ACLK=VLOCLK
    CSCTL0_H = 0x00;                        // Lock CS module (use byte mode to upper byte)

    // P1.0 (left LED)
    P1OUT &= ~0x01;                         // Clear P1.0 output
    P1DIR |= 0x01;                          // Set P1.0 to output direction

    PM5CTL0 &= ~LOCKLPM5;
    uart_init();
    temp_init();
    __delay_cycles(1000);                   // Allow clock system to settle
    clock_init();


    __bis_SR_register(LPM0_bits | GIE);
    __no_operation();
}


void __attribute__ ((interrupt(TIMER0_A1_VECTOR))) Timer0_A1_ISR (void)
{
    switch(TA0IV) {
        case TAIV__TACCR1:
            break;
        case TAIV__TACCR2:
            timestamps[i++] = TA0CCR2;

            if (i >= 20) {
                print_timestamps();
                while (1) {
                    P1OUT ^= 0x01;                    // Toggle P1.0 (LED)
                    __delay_cycles(100000);
                }
            }
            break;
        case TAIV__TAIFG:
            break;
        default:
            break;
    }
}