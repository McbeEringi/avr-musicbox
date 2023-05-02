TARGET:=main
HEDS:=
SRCS:=main.c
CC:=avr-gcc
CFLAGS:=-Os -mmcu=attiny202
RM:=cmd.exe /C del

.PHONY: clean

OBJS:=$(addprefix .tmp/,$(SRCS:.c=.o))
HEDS:=$(addprefix src/,$(HEDS))
SRCS:=$(addprefix src/,$(SRCS))

$(TARGET).hex: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o .tmp/$(TARGET).out
	avr-size .tmp/$(TARGET).out
	avr-objcopy -F ihex .tmp/$(TARGET).out $(TARGET).hex

.tmp/%.o: src/%.c $(HEDS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) /q .tmp
	$(RM) $(TARGET).hex

write: $(TARGET).hex
	avrdude -v -p t202 -c serialupdi -P COM3 -U flash:w:$(TARGET).hex:a