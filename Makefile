.PHONY: main write clean

CC=avr-gcc
FILE=src/main.c
CFLAGS=-mmcu=attiny1604 -DF_CPU=20e6 -Os ${FILE}

main:write clean
write:main.elf
	 - avrdude -v -c serialupdi -xrtsdtr=high -p t1604 -P /dev/$(shell ls /sys/bus/usb-serial/devices|tail -n1) -U flash:w:main.elf
main.elf:
	${CC} ${CFLAGS} -o main.elf
main.S:
	${CC} -S ${CFLAGS} -o main.S
clean:
	- rm main.elf main.S
compiledb:
	@ echo -e "[{\n\t\"directory\":\"$(dir $(abspath $(lastword $(MAKEFILE_LIST))))\",\n\t\"command\":\"${CC} ${CFLAGS}\",\n\t\"file\":\"${FILE}\"\n}]">compile_commands.json
