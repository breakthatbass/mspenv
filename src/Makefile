
ifndef $(MSPGCCDIR)
	MSPGCCDIR=$(HOME)/ti/msp430-gcc
endif

PROG=butled1.elf

# paths
INC_DIR = $(MSPGCCDIR)/include
# mspdebug needs the path for the driver
TILIB_PATH=$(MSPGCCDIR)/bin/

DEVICE=msp430fr5994

CC=$(MSPGCCDIR)/bin/msp430-elf-gcc


CLFAGS = -I . -I $(INC_DIR) -mmcu=$(DEVICE) -g -02
LFLAGS = -L . -L $(INC_DIR) -T $(DEVICE).ld

# mspdebug driver
DRIVER:=tilib

all: $(PROG)

%.elf: %.c
	$(CC) $(CFLAGS) $(LFLAGS) $< -o $@

#asm:
#	$(CC) $(CFLAGS) -D_GNU_ASSEMBLER_  ledsasm.S -o ledsasm.elf

# upload
install:
	export MSPDEBUG_TILIB_PATH=$(TILIB_PATH)
	mspdebug $(DRIVER) "prog $(PROG)" --allow-fw-update

clean:
	rm -f *.o *.elf
