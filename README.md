# msp430-env

A text editor development environment, bunch of small standalone programs, and a UART library for the `msp430fr5994` microcontroller. The goal here is to learn more about writing firmware and then having a reference.

All the code here can be compiled and flashed by using the `Makefile` in the root directory.

## Setting up the development environment
To do anything in this repo there is some setup. We'll need a compiler, header file libs, and something to flash the firmware onto the board.

Dowload the [`msp430-gcc`](https://www.ti.com/tool/MSP430-GCC-OPENSOURCE) toolchain and put the directory into your `$HOME` directory.  
And clone, build, and install [`mspdebug`](https://github.com/dlbeer/mspdebug) for flashing.

For full setup instructions, see the [setup page](https://github.com/breakthatbass/msp430-env/wiki/Setup#development-environment) in the wiki.

## Usage

**Compilation**:

Compile all `.c` files (must be in the `src` directory):
```
make
```
Running `make` will compile all `.c` files into an equivalent `.elf` file and place them all in a directory named `elves`...🧝.

**Flashing**:
```
make install a=<prog_name>
```
If you want to upload a program called `blink.elf`, you would use `make install a=blink`. It will look in the `elves` directory for it.

**Compiler info**:
```
make help
```