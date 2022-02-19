
ifndef $(MSPGCCDIR)
	MSPGCCDIR=$(HOME)/ti/msp430-gcc
endif

# paths
INC_DIR = $(MSPGCCDIR)/include

DEVICE=msp430fr5994

CC=$(MSPGCCDIR)/bin/msp430-elf-gcc

GDB=$(MSPGCCDIR)/bin/msp430-elf-gdb

# place the .elf files in the elves dir
BUILD=build

# get all .c files
SRCS=$(wildcard src/*.c)
LIBS=$(wildcard lib/*.c)

BINS=$(patsubst src/%.c, $(BUILD)/%.elf, $(SRCS))


CFLAGS  = -I . -I $(INC_DIR) -mmcu=$(DEVICE)
LFLAGS := -L . -L $(INC_DIR) -T $(DEVICE).ld

DEBUG_FLAGS := -O0 -g3 -ggdb -gdwarf-2

CFLAGS+=$(DEBUG_FLAGS)

# mspdebug driver
DRIVER:=tilib

#------------------------------------------------#

all: $(BUILD)/$(BINS)

$(BUILD)/%.elf: src/%.c | $(BUILD)
	$(CC) $(CFLAGS) $(LFLAGS) $(LIBS) $< -o $@


$(BUILD):
	mkdir -p $(BUILD)


# show compiler help menu
help:
	$(CC) -v --help

# open a TCP port to use gdb on the board
# usage: make gdb a=binary
gdb:
	mspdebug $(DRIVER) "gdb" & \
	$(GDB) -q $(BUILD)/$(a).elf \
	-ex "target remote localhost:2000"

# upload to baord
# USAGE: make install a=binary
install:
	mspdebug $(DRIVER) "prog $(BUILD)/$(a).elf" --allow-fw-update


clean:
	rm -rf $(BUILD)
