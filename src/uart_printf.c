 /**
 * uart_printf.c - a simple program to test out the uartprintf() function.
 *
 * an FTDI cable is needed to connect the UART pins to the computer.
 * from there run the command `screen <location-of-device> <baud rate>`
 * and that will open the console.
 *
 * in this case on MacOS I ran:
 *
 * screen /dev/cu.usbserial-AR0JW545 9600
 * */
#include <msp430.h>
#include <lib/uartio.h>

void main(void) {
	WDTCTL = WDTPW | WDTHOLD;   //Stop watchdog timer
	PM5CTL0 &= ~LOCKLPM5;

	uart_init();
	uart_puts("\nprintf tests\n");

	unsigned char *name = "Taylor";
	unsigned int r = 34;

	uart_printf("hello, my name is %s and I am %d years old.\n", name, r);

	// test out the hex capability
	// turn on LED P1.1 (right side green LED)
	P1DIR |= BIT1;
	uart_printf("P1DIR: %x\n", P1DIR);
	P1OUT |= BIT1;
	uart_printf("P1OUT: %x\n", P1OUT);
	uart_puts("\ntesting puts for hex vals:\n");
	uart_putx(P1OUT);

	while (1);
}