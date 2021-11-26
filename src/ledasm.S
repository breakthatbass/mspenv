#include <msp430fr5994.h>

	ORG		0xF000		; start of 4k flash memory
Reset:
	mov.w	#WDTPW | WDTHOLD, &WDTCTL
	mov.w	#~LOCKLPM5, &PM5CTL0
	
	mov.b	#00000011, &P1DIR
	mov.b	#00000011, &P1OUT

InfLoop:
	jmp		InfLoop

	ORG		0xFFFE
	DW		Reset
	END
