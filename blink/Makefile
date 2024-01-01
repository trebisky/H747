# Makefile for blink demo
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

OBJS = locore.o main.o gpio.o rcc.o

all: blink.bin blink.dump

blink.dump:	blink.elf
	$(DUMP) blink.elf >blink.dump

blink.bin:	blink.elf
	$(OBJCOPY) blink.elf blink.bin -O binary

blink.elf: 	$(OBJS)
	$(LD) -T blink.lds -o blink.elf $(OBJS)

spin.elf: 	spin.o
	$(LD) -T blink.lds -o spin.elf spin.o

#locore.o:	locore.s
#	$(AS) locore.s -o locore.o

locore.o:	locore.S
	$(CC) -c locore.S -o locore.o

OCDCFG = -f /usr/share/openocd/scripts/board/stm32h747i-disco.cfg

flash:  blink.elf
	openocd $(OCDCFG) -c "program blink.elf verify reset" -c "exit"

# Not tested, but this might work ..
burnit:
	openocd $(OCDCFG) -c "init" -c "flash write_image erase blink.bin 0x08000000" -c "exit"

# Also not tested
burnit2:
	st-flash write blink.bin 0x08000000

clean:
	rm -f *.o blink.elf blink.bin blink.dump
