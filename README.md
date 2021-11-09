# MSP430

This repo holds a bunch of code for the TI MSP430FR5994 microcontroller. This is my learning process.

All the code here can be compiled and flashed by using the Makefile in the root directory.

## Setting up
To do anything in this repo there is some setup. We'll need a compiler, header file libs, and something to flash the firmware onto the board.

- Compiler, toolchain, headers: [msp430-gcc](https://www.ti.com/tool/MSP430-GCC-OPENSOURCE)
- Flasher: [mspdebug](https://github.com/dlbeer/mspdebug)

## Usage

**Compilation**:

Compile all `.c` files (must be in the `src` directory):
```
make
```
Running `make` will compile all `.c` files into an equivalent `.elf` file and place them all in a directory named `elves`...🧝 pun intended.

**Flashing**:
```
make install a=<prog_name>
```
If you want to upload a program called `blink.elf`, you would use `make install blink`. It will look in the `elves` directory for it.
