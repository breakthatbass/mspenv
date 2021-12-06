#include <msp430.h>
#include "../lib/uartio.h"

#define DELAY 50000L
#define BUF 100

unsigned long _atoi(char *s)
{
	unsigned long res = 0;
	int i;
	
	for (i = 0; s[i] != '\0'; ++i) {
		res = res * 10 + s[i] - '0';
	}
	return res;
}

void setzero(char *s, int size)
{
	for (int i = 0; i < size; i++) {
		s[i] = 0;
	}
}




int read_line(char *buf, unsigned int size)
{
	int i = 0;
	char c;
	while ((c = _getchar()) && i < size) {
		if (c == -1) continue;  // waiting...
		else if (c == '\n') {
			*buf = '\0';
			break;
		}
		else if (c == '\r') {
			return 0;
		}
		*buf = c;
		buf++;
		i++;
	}
	return i;
}


void main(void) {
  WDTCTL = WDTPW | WDTHOLD;   //Stop watchdog timer
  PM5CTL0 &= ~LOCKLPM5;

  uart_init();
  
  char buf[BUF] = {0};
  int i = 0;

  unsigned long total = 0;
  unsigned long prev = 99999999;
  unsigned long cur = 0;
 
  while (1) {

		total = 0;
		
		while (read_line(buf, BUF)) {
			cur = _atoi(buf);
			if (cur > prev) total++;
			prev = cur;
		}
		__delay_cycles(DELAY);
		uartprintf("TOTAL: %u\n\r", total);
	}
}


