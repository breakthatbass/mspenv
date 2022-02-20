# msp430 LCD device driver documentation
a simple API to make use of an LCD with an msp430
 
#
```C
void lcd_init(unsigned int blink_option) 
```
initialize LCD driver
- `blink_option` - set the cursor blinker on/off. `BLINK_ON` or `BLINK_OFF`.

<br>

```C
void lcd_clear(void) 
```
clear the LCD screen.

<br>

```C
void lcd_putc(unsigned char c) 
```
print a single byte/char to the LCD screen
- `c` - the char to print.

<br>

```C
void lcd_puts(char *s) 
```
print a string to an LCD and wrap text into the second line.
- `s` - the string to print.

<br>

```C
void lcd_puts_xy(int x, int y, char *s) 
```
print a string to the LCD in a specific location.
- `x` - horizonal placement of cursor (0-15).
- `y` - vertical placement of cursor (0-1).
- `s` - the string to write.

<br>

```C
void lcd_putc_xy(int x, int y, unsigned char c) 
```
print a char to the LCD in a specific location.
- `x` - horizonal placement of cursor (0-15).
- `y` - vertical placement of cursor (0-1).

<br>

```C
void lcd_goto(int x, int y) 
```
move the cursor to a specific location.
- `x` - horizonal placement of cursor (0-15).
- `y` - vertical placement of cursor (0-1).

<br>

```C
void lcd_printf(char *fmt, ...) 
```
printf for the LCD. Conversions: `%x`, `%c`, `%d`, `%s`.
- `fmt` - the string to print.
- `...` - the list of variables to fill in.

<br>

