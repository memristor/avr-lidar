# Actuator Control Board

## Cross-compilation
Install required packages
```
apt-get install avr-binutils avr-gcc avr-libc avrdude
```
and run
```
make program
```
you should now get successfully flashed microcontroller.


## Fuse bits
By default at90can128 uses internal oscillator (8MHz) and to configure external 
oscillator we have to configure fuse bits using command:
```
avrdude -p at90can128 -c usbasp -U lfuse:w:0x9F:m
```