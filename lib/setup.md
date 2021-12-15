# Setup Help
Directions and information for setting up different programs and peripherals.


# Development Environment
To do anything in this repo there is some setup. We'll need a cross-compiler, header file libs, and something to flash the firmware onto the board.

- Compiler, toolchain, headers: [msp430-gcc](https://www.ti.com/tool/MSP430-GCC-OPENSOURCE)
- Flasher: [mspdebug](https://github.com/dlbeer/mspdebug)
- `mspdebug` looks to an environment variable for a filepath for the `tilib` library. That can be set by runnig the command `export MSPDEBUG_TILIB_PATH=$HOME/ti/msp430-gcc/bin/` before using it. But it's just easier to add it to your `.bash_profile` or `.zshrc` or whatever you use.

Something like this would work:
```
echo export MSPDEBUG_TILIB_PATH=$HOME/ti/msp430-gcc/bin/ >> $HOME/.zshrc
```

The `msp430-gcc` toolchain comes downloaded as a directory called `ti`. The `ti` directory needs to be in the `$HOME` directory for the Makefile to work. You can always change the Makefile if you want it in a different location.

### **msp430-gcc Usage**

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
<br>

# UART
In order to make use of the uartio lib, there is some physical setup. You'll need an [FDTI USB to Serial adapter](https://www.amazon.com/dp/B07RBK2P47?psc=1&ref=ppx_yo2_dt_b_product_details) and connect it to your board on one end, and your PC on the other end. This is how data is sent back and forth between the two systems.

The `uart_init()` function is required before any reading and writing through uart. You can write your own function for that, but I wrote for quick setup. The default baud rate is 9600 and it sets port 2 pin 5 to output and port 2 pint 6 to input.

![uart](../img/uart.jpg)

On the FDTI cable I have (the one linked above), there are six cables to use, you really only need to make use of the orange and yellow which the orange is for input and the yellow is for output. You can connect power and ground but here since we're flashing programs constantly, we already have power through the other USB connector. At the very least connect your jumper cables like the above picture.

[picture of jumpers on board]

Connect the other end of the jumpers to the pins you're using for uart. If you're using the `uart_init()` function from the lib, that would be yellow to port 2 pin 5 and orange to port 2 pin 6 like the picture above.

### Opening a console
There are many ways to open up a console to communicate with the board. On both Linux and MacOS the `screen` command works fine. It works like this:
```
screen <FDTI-cable-location> <baude-rate>
```
On my MacOS system, I run this:
```
screen /dev/cu.usbserial-AR0JW545 9600
```
It's very likely you'll have to change the `<FDTI-cable-location>`. To find it you can run one of these commands:

**MacOS**
```
ls /dev/cu.usb* | awk '{print $1}'
```

**Linux**
```
# Linux
ls /dev/ttyACMO
ls /dev/serial/by-id
ls /dev/serial/by-path
```

Something should be returned with usbserial in the name if it's plugged in.  

Now run your program and open a console and you should be good to go.

**NOTE:** It seems if you close the console and try to open it back up again it will be considered "busy" and thus not be able to open a console. Just unplug the FDTI USB end and plug it back in and it should work.

<br>

# Breadboard Programs
A handful of the programs require the use of connecting the MCU to a breadboard with jumper cables such as [`breadboardled.c`](https://github.com/breakthatbass/msp430-env/blob/main/src/breadboardled.c) and [`breadswitch.c`](https://github.com/breakthatbass/msp430-env/blob/main/src/breadswitch.c).  

If you don't have any of the supplies, you can get everything you need [here](https://www.amazon.com/gp/product/B073ZC68QG/ref=ppx_yo_dt_b_asin_title_o02_s00?ie=UTF8&psc=1).  

Using a breadboard with the MCU is pretty simple. If you need to learn the basics of how breadboards and electricity works, search YouTube. There are a lot of helpful videos. I won't explain how the programs above need to be put together, as they are self-evident if you understand breadboard basics, however, I will explain connecting to any peripherals since those tend to have their own datasheets and requirements.