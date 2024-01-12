# Makefile for serial demo
#
# First code for the STM32H747

TOOLS = arm-none-eabi

# Assembling with gcc (without -c) makes it want crt0 at link time.
#AS = $(TOOLS)-gcc
AS = $(TOOLS)-as

# Use the -g flag if you intend to use gdb
#CC = $(TOOLS)-gcc -mcpu=cortex-m7 -mthumb
CC = $(TOOLS)-gcc -mcpu=cortex-m7 -mthumb -g

#LD = $(TOOLS)-gcc
LD = $(TOOLS)-ld.bfd
OBJCOPY = $(TOOLS)-objcopy
DUMP = $(TOOLS)-objdump -d
GDB = $(TOOLS)-gdb

OBJS = locore.o main.o gpio.o rcc.o usart.o

all: serial.bin serial.dump

serial.dump:	serial.elf
	$(DUMP) serial.elf >serial.dump

serial.bin:	serial.elf
	$(OBJCOPY) serial.elf serial.bin -O binary

serial.elf: 	$(OBJS)
	$(LD) -T h747.lds -o serial.elf $(OBJS)

spin.elf: 	spin.o
	$(LD) -T h747.lds -o spin.elf spin.o

#locore.o:	locore.s
#	$(AS) locore.s -o locore.o

locore.o:	locore.S
	$(CC) -c locore.S -o locore.o

OCDCFG = -f /usr/share/openocd/scripts/board/stm32h747i-disco.cfg

flash:  serial.elf
	openocd $(OCDCFG) -c "program serial.elf verify reset" -c "exit"

# Not tested, but this might work ..
burnit:
	openocd $(OCDCFG) -c "init" -c "flash write_image erase serial.bin 0x08000000" -c "exit"

# Also not tested
burnit2:
	st-flash write serial.bin 0x08000000

clean:
	rm -f *.o serial.elf serial.bin serial.dump
	rm -f spin.elf
