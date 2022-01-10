/**
 * lcd_driver_tests.c - a program to test different driver functions
 * to interact with an LCD
 *
 * Taylor Gamache
 * Jan 4, 2022
 * */
#include <msp430fr5994.h>
#include "../lib/lcd.h"

#define SEC 2000000

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // put the dawg to sleep
    PM5CTL0 &= ~LOCKLPM5;       // unlock ports

    // init LCD with cursor blinking set to off
    lcd_init(BLINK_OFF);
	char *n = "tay";
	int age = 82;

	lcd_printf("name: %s a %d", n, age);

	__delay_cycles(SEC);
	lcd_clear();

    // print a single char to LCD
    lcd_putc('a');

    // hold for about a second then clear LCD
    __delay_cycles(SEC);
    lcd_clear();

    // print a string to LCD and wrap it to 2nd row
    lcd_puts("hello, my name is taylor. LCDs are cool");

    __delay_cycles(SEC);
    lcd_clear();

    // print a string starting at a specific x, y point
    lcd_print_xy("aloha", 3, 1);

    while(1);
}
