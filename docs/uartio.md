# uartio documentation
a simple and easy to use API for connecting an msp430 to another device through UART.
 
#
```C
void uart_putc(unsigned char byte) 
```
quickly set up a UART connection on port 2 pins 5 and 6.
Send a single byte to the transmit buffer register.
- `byte` - byte to send to transmit buffer register.

<br>

```C
unsigned char uart_getc(void) 
```
attempt to read a byte stored in the recieve buffer register.
- **returns** when a byte is recieved .

<br>

```C
void uart_puts(char *s) 
```
print a string through UART
- `s` - print each `char` in `s` to an open UART console.

<br>

```C
char *uart_gets(char *buf, int limit) 
```
read an entire line/string into `buf`.
- `buf` - the buffer to read the bytes into.
- `limit` - the limit of bytes to read into `buf`.
- **returns** `buf` with the bytes stored in its memory space.

<br>

```C
void uart_putx(unsigned n) 
```
print a hex value
- `n` - an unsigned integer.

<br>

```C
void uart_printf(char *fmt, ...) 
```
printf but for the msp430 MCU to print to UART.
- `fmt` - the string to print.
- `...` - the list of variables to fill in.

<br>

