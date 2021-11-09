
ifndef $(MSPGCCDIR)
	MSPGCCDIR=$(HOME)/ti/msp430-gcc
endif

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

all: ledson.elf

%.elf: %.c
	$(CC) $(CFLAGS) $(LFLAGS) $< -o $@

# ./mspdebug $(DRIVER) --force-reset "prog blink.elf" --allow-fw-update
# upload
install:
	export MSPDEBUG_TILIB_PATH=$(TILIB_PATH)
	mspdebug $(DRIVER) --force-reset "prog blink.elf" --allow-fw-update

clean:
	rm -f *.o *.elf
