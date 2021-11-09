# elf factory

🧝 A bunch of code for the msp430 microcontroller. Yes, it all compiles to `.elf` files.

All the code here can be compiled and flashed by using the `Makefile` in the root directory.

## Setting up the development environment
To do anything in this repo there is some setup. We'll need a compiler, header file libs, and something to flash the firmware onto the board.

- Compiler, toolchain, headers: [msp430-gcc](https://www.ti.com/tool/MSP430-GCC-OPENSOURCE)
- Flasher: [mspdebug](https://github.com/dlbeer/mspdebug)
- `mspdebug` looks to an environment variable for a filepath for the `tilib` library. That can be set by runnig the command `export MSPDEBUG_TILIB_PATH=$HOME/ti/msp430-gcc/bin/`. But it's just easier to add it to your `.bash_profile` or `.zshrc` or whatever you use.


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
If you want to upload a program called `blink.elf`, you would use `make install a=blink`. It will look in the `elves` directory for it.