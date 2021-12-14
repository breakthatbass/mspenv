#ifndef __UARTIO_H__
#define __UARTIO_H__


// printf but for the msp430 and UART
void uartprintf(char *format, ...);

// push byte to transfer register 
void uartputc(unsigned char byte);

// recieve byte frim recieve register
int uartgetc(void);

// print all bytes in a string to transfer register
void uartputs(char *s);

// get string from user and push all bytes to recieve register
char *uartgets(char *buf, int limit);

// set up port/pins for uart communication
void uart_init(void);

#endif
