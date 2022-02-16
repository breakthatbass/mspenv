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
    lcd_init(BLINK_ON);

    __delay_cycles(SEC);

    //lcd_goto(4, 1);

    //__delay_cycles(SEC);
    //lcd_putc('c');
    //__delay_cycles(SEC);
    //lcd_goto(13, 0);
    //__delay_cycles(SEC);
    //lcd_putc('d');
	lcd_printf(0,0, "hello in there!");
	__delay_cycles(SEC);
	lcd_puts("poo berries");

    /*
	lcd_printf(3, 1, "my name is %s", n);

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
    */

    while(1);
}
