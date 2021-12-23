# msp430-env

This repo contains everything I learn about embedded systems and working with the `msp430fr5994` MCU. The purpose here is to provide an environment to quickly get working with minimal project setup and easily compile and flash programs to the board. This way I can also easily reference everything.

A quick rundown of what this repo contains:
- Text editor development environment - write code with Vim instead of CCS. The `Makefile` handles everything.
- A bunch of standalone, installable programs. See the [`src`](https://github.com/breakthatbass/msp430-env/tree/main/src) directory for a program list & descriptions. See [usage](https://github.com/breakthatbass/msp430-env/#Usage) below on how to install a program to your board.
- Libs/drivers - a uart library and an LCD driver library. See the [`lib`](https://github.com/breakthatbass/msp430-env/tree/main/lib) directory for source code, docs, and setup instructions.

## Setting up the development environment
To do anything in this repo there is some setup. We'll need a compiler, header file libs, and something to flash the firmware onto the board.

Dowload the [`msp430-gcc`](https://www.ti.com/tool/MSP430-GCC-OPENSOURCE) toolchain and put the directory into your `$HOME` directory.  
And clone, build, and install [`mspdebug`](https://github.com/dlbeer/mspdebug) for flashing.

For full setup instructions and more details than here, see the [setup page](https://github.com/breakthatbass/msp430-env/wiki/Setup#development-environment) in the [wiki](https://github.com/breakthatbass/msp430-env/wiki).

## Usage

**Setting up a new project**  

Create a new `.c` file in the `src` directory. That's it!  
To use a lib or driver, simply include the header file(s). The `Makefile` takes care of the rest.

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