# Makefile for printf demo
#
# First code for the STM32H747

TOOLS = arm-none-eabi

# Assembling with gcc (without -c) makes it want crt0 at link time.
#AS = $(TOOLS)-gcc
AS = $(TOOLS)-as

# Use the -g flag if you intend to use gdb
#CC = $(TOOLS)-gcc -mcpu=cortex-m7 -mthumb
COPTS = -mcpu=cortex-m7 -mthumb
COPTS += -fno-builtin
CC = $(TOOLS)-gcc $(COPTS) -g

#LD = $(TOOLS)-gcc
LD = $(TOOLS)-ld.bfd
OBJCOPY = $(TOOLS)-objcopy
DUMP = $(TOOLS)-objdump -d
GDB = $(TOOLS)-gdb

OBJS = locore.o main.o gpio.o rcc.o usart.o random.o prf.o

all: print.bin print.dump

print.dump:	print.elf
	$(DUMP) print.elf >print.dump

print.bin:	print.elf
	$(OBJCOPY) print.elf print.bin -O binary

print.elf: 	$(OBJS)
	$(LD) -T h747.lds -o print.elf $(OBJS)

#locore.o:	locore.s
#	$(AS) locore.s -o locore.o

locore.o:	locore.S
	$(CC) -c locore.S -o locore.o

OCDCFG = -f /usr/share/openocd/scripts/board/stm32h747i-disco.cfg

flash:  print.elf
	openocd $(OCDCFG) -c "program print.elf verify reset" -c "exit"

# Not tested, but this might work ..
burnit:
	openocd $(OCDCFG) -c "init" -c "flash write_image erase print.bin 0x08000000" -c "exit"

# Also not tested
burnit2:
	st-flash write print.bin 0x08000000

clean:
	rm -f *.o print.elf print.bin print.dump
