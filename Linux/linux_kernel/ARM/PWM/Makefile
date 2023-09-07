CROSS = arm-none-eabi-
CC = $(CROSS)gcc
LD = $(CROSS)ld
OBJCOPY = $(CROSS)objcopy
OBJDUMP = $(CROSS)objdump

all:
	$(CC) -fno-builtin -nostdinc -c -o start.o start.S
	$(CC) -fno-builtin -nostdinc -c -o main.o main.c
	$(LD) start.o main.o -Tmap.lds -o uart.elf
	$(OBJCOPY) -O binary -S uart.elf uart.bin
	$(OBJDUMP) -D uart.elf > uart.dis

clean:
	rm -f *.o *.elf *.bin *.dis
