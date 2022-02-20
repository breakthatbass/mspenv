Some of the programs here make use of peripherals and libs. See directions for hooking up the peripherals and docs for the libs in the [wiki](https://github.com/breakthatbass/mspenv/wiki).

**note:** For making use of the UART programs, run the [`connect`](https://github.com/breakthatbass/mspenv/blob/main/connect) script to open a console.


### Programs

- [`ledson.c`](https://github.com/breakthatbass/msp430-env/blob/main/src/ledson.c) - light up both LEDs.
- [`blink.c`](https://github.com/breakthatbass/msp430-env/blob/main/src/blink.c) - blink left LED with a 1 second delay.
- [`blink_both_LEDs.c`](https://github.com/breakthatbass/msp430-env/blob/main/src/blink_both_LEDS.c) - blink both LEDs at the same time.
- [`blink_LED_alt.c`](https://github.com/breakthatbass/msp430-env/blob/main/src/blink_LED_alt.c) - blink both LEDs alternately. if one is on, the other is off.
- [`timerled.c`](https://github.com/breakthatbass/msp430-env/blob/main/src/timerled.c) - toggle both LEDs by using a timer rather than a delay.
- [`buttons.c`](https://github.com/breakthatbass/msp430-env/blob/main/src/buttons.c) - left button turns on the left LED, right button turns on the right LED.
- [`breadboardled.c`](https://github.com/breakthatbass/msp430-env/blob/main/src/breadboardled.c) - blink an LED on a breadboard.
- [`breadswitch.c`](https://github.com/breakthatbass/msp430-env/blob/main/src/breadswitch.c) - blink an LED on a breadboard by pressing a switch.
- [`printf.c`](https://github.com/breakthatbass/msp430-env/blob/main/src/printf.c) - a simple program to test out the `uartprintf()` function.
- [`getchar.c`](https://github.com/breakthatbass/msp430-env/blob/main/src/getchar.c) - take input through UART and print it out.
- [`timestamps.c`](https://github.com/breakthatbass/msp430-env/blob/main/src/timestamps.c) - record timestamps from CPU clock at interrupts and record into an array.
- [lcd_driver_tests.c](https://github.com/breakthatbass/mspenv/blob/main/src/lcd_driver_tests.c) - a small program I use to test different parts of the [lcd driver](https://github.com/breakthatbass/mspenv/blob/main/lib/lcd.c) when I need to.
- [lcd_write_input.c](https://github.com/breakthatbass/mspenv/blob/main/src/lcd_write_input.c) - read in keypresses through UART and print on the lcd.
- [uart_getc.c](https://github.com/breakthatbass/mspenv/blob/main/src/uart_getc.c) - read in one char at a time from UART and print it out to the console.
- [uart_gets.c](https://github.com/breakthatbass/mspenv/blob/main/src/uart_gets.c) - read in a line into a buffer through UART then print it to the console.
- [uart_printf.c](https://github.com/breakthatbass/mspenv/blob/main/src/uart_printf.c) - a small program to test the printf function.