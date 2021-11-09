
ifndef $(MSPGCCDIR)
	MSPGCCDIR=$(HOME)/ti/msp430-gcc
endif

# paths
INC_DIR = $(MSPGCCDIR)/include
# mspdebug needs the path for the driver
TILIB_PATH=$(MSPGCCDIR)/bin/

DEVICE=msp430fr5994

CC=$(MSPGCCDIR)/bin/msp430-elf-gcc

# get all .c files
SRCS=$(wildcard src/*.c)

BINS=$(patsubst src/%.c, $(ELFDIR)/%.elf, $(SRCS))

# place the .elf files in the elves dir
ELFDIR=elves
ELVES=$(addprefix $(ELFDIR)/,$(notdir  $(SRCS:.c=.elf)))



CLFAGS = -I . -I $(INC_DIR) -mmcu=$(DEVICE) -g -02
LFLAGS = -L . -L $(INC_DIR) -T $(DEVICE).ld

# mspdebug driver
DRIVER:=tilib

all: $(ELFDIR)/$(BINS)

$(ELFDIR)/%.elf: src/%.c | $(ELFDIR)
	$(CC) $(CFLAGS) $(LFLAGS) $< -o $@

$(ELFDIR):
	mkdir -p $(ELFDIR)

# upload to baord
# USAGE: make install a=binary
install:
	export MSPDEBUG_TILIB_PATH=$(TILIB_PATH)
	mspdebug $(DRIVER) "prog $(ELFDIR)/$(a).elf" --allow-fw-update

clean:
	rm -rf elves
