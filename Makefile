all:
	avr-gcc -DF_CPU=1000000UL -mmcu=attiny2313 -I. -gdwarf-2 -Os -o main.o main.c
	avr-objcopy -O ihex main.o main.hex
