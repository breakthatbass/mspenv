#include <msp430.h>
#include <stdio.h>
#include "../lib/uartio.h"

void UART_init(void);

void main(void) {
  WDTCTL = WDTPW | WDTHOLD;   //Stop watchdog timer
  PM5CTL0 &= ~LOCKLPM5;

  UART_init();
  
  char buf[100];
  int c;
  int i = 0;

  
  while (1) {
        uartprintf("> ");
		while ((c = _getchar())) {
			
			if (c == -1) continue;

			uartprintf("%c", (char)c);
			buf[i++] = c;
			if (c == '\n') {
				uartprintf("\n\n");
				break;
			}
		}
		buf[i] = '\0';
		uartprintf("%s\n", buf);
        
		__delay_cycles(500000L);
	}
}


