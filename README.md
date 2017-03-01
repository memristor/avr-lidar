# Lidar  Board

## Cross-compilation
Install required packages
```
apt-get install avr-binutils avr-gcc avr-libc avrdude
```
and run
```
sudo make program
```
you should now get successfully flashed microcontroller.

If you use JTAG programmer, in makefile change instead of "usbasp" put "jtag1"
and instead of "com1" put "/dev/ttyUSB0".
```
avrdude -p at90can128 -P /dev/ttyUSB0 -c jtag1 -U flash:w:lidar_board.hex -F
```

## Fuse bits
By default at90can128 uses internal oscillator (8MHz) and to configure external 
oscillator we have to configure fuse bits using command:
```
avrdude -p at90can128 -c usbasp -U lfuse:w:0x9F:m
```
