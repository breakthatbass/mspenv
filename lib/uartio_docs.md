# uartio documentation
a handful of basic functions to read and write to UART for the msp430 MCU.
 
#
```C
void uartprintf(char *format, ...) 
```
`printf` but for the msp430 MCU to print to UART. Requires `uart_init()`.

<br>

```C
void uartputs(char *s) 
```
print a string through UART
- `s` - print each `char` in `s` to an open UART console.

<br>

```C
void uartputc(unsigned char byte) 
```
Send a single byte to the transmit buffer register.
- `byte` - byte to send to transmit buffer register.

<br>

```C
int uartgetc(void) 
```
attempt to read a byte stored in the recieve buffer register.
- **returns** byte if found, else return `-1`.

<br>

```C
char *uartgets(char *buf, int limit) 
```
read an entire line/string into `buf`.
- `buf` - the buffer to read the bytes into.
- `limit` - the limit of bytes to read into `buf`.
- **returns** `buf` with the bytes stored in its memory space.

<br>

