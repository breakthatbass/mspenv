; ledasm.s43 - a simple assembly program to light LEDs
; Lights pattern of LEDs, sets the pins to output, then loops forever
; from page 72
;--------------------------------------------------------------------

#include "../../../ti/msp430-gcc/include/msp430fr5994.h"

	ORG		0xf000							; start of 4KB flash memory
Reset:
	mov.w		#WDTPW|WDTHOLD,&WDTCTL		; stop watchdog timer
	mov.b		#00001000b,&P2OUT				; LED2 (P2.4) on, LED1 (p2.3) off
	mov.b		#00011000b, &P2DIR			; Set pins with LEDs to output
InfLoop:
	jmp:		InfLoop							; ...doing nothing
;--------------------------------------------------------------------
	ORG		0xfffe							; address of msp430 reset vector
	DW			Reset								; addtress of start execution
	END
