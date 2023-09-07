CROSS = arm-none-eabi-
CC = $(CROSS)gcc
LD = $(CROSS)ld
OBJCOPY = $(CROSS)objcopy

all: led.s
	$(CC) -g -c -o led.o led.s
	$(LD) -Ttext 0x40001000 led.o -o led.elf
	$(OBJCOPY) -O binary -S led.elf led.bin
	$(CROSS)objdump -D led.elf > led.dis

clean:
	rm -f *.o *.elf *.bin *.dis
