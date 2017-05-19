# Lidar  Board

## Cross-compilation
Install required packages  
- Debian (Ubuntu) `sudo apt-get install binutils-avr gcc-avr avr-libc avrdude`
- Arch `sudo pacman -S avr-binutils avr-gcc avr-libc avrdude`

and run `sudo make program` (or `sudo make program AVRDUDE_PROGRAMMER=jtag1 AVRDUDE_PORT=/dev/ttyUSB0` for JTAG)
you should now get successfully flashed microcontroller.

## Fuse bits
By default at90can128 uses internal oscillator (8MHz) and to configure external 
oscillator we have to configure fuse bits using command:
```
avrdude -p at90can128 -c usbasp -U lfuse:w:0x9F:m
```
