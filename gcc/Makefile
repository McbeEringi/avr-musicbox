TARGET:=main
HEDS:=sheet.h
SRCS:=main.c
CC:=avr-gcc
CFLAGS:=-Os -mmcu=attiny85
RM:=cmd.exe //C del

.PHONY: clean

OBJS:=$(addprefix tmp/,$(SRCS:.c=.o))
HEDS:=$(addprefix src/,$(HEDS))
SRCS:=$(addprefix src/,$(SRCS))

$(TARGET).hex: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET).out
	avr-objcopy -F ihex $(TARGET).out $(TARGET).hex

tmp/%.o: src/%.c $(HEDS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) tmp/*.o
	$(RM) $(TARGET).out $(TARGET).hex
