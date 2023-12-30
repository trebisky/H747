# Makefile for debug demos
#
# First code for the STM32H747

TOOLS = arm-none-eabi

# Assembling with gcc makes it want crt0 at link time.
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

OBJS = locore.o main.o

all: debug.bin debug.dump

debug.dump:	debug.elf
	$(DUMP) debug.elf >debug.dump

debug.bin:	debug.elf
	$(OBJCOPY) debug.elf debug.bin -O binary

debug.elf: 	$(OBJS)
	$(LD) -T debug.lds -o debug.elf $(OBJS)

locore.o:	locore.s
	$(AS) locore.s -o locore.o

OCDCFG = -f /usr/share/openocd/scripts/board/stm32h747i-disco.cfg

flash:  debug.elf
	openocd $(OCDCFG) -c "program debug.elf verify reset" -c "exit"

# Not tested, but this might work ..
burnit:
	openocd $(OCDCFG) -c "init" -c "flash write_image erase debug.bin 0x08000000" -c "exit"

# Also not tested
burnit2:
	st-flash write debug.bin 0x08000000

clean:
	rm -f *.o debug.elf debug.bin debug.dump
