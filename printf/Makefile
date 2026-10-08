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

#OBJS = locore.o startup.o main.o gpio.o rcc.o usart.o random.o prf.o
#OBJS = locore.o rcc.o main.o gpio.o usart.o random.o prf.o
#OBJS = locore.o main.o gpio.o rcc.o usart.o random.o prf.o

# For some odd reason, putting startup.o in the link list
# makes things run slow.  Sometimes.
# And we aren't even calling the function in startup.o
# (which is why we can remove or add it to the link list).

#OBJS = locore.o startup.o main.o gpio.o rcc.o usart.o random.o prf.o delay.o SLOW
#OBJS = locore.o main.o startup.o gpio.o rcc.o usart.o random.o prf.o delay.o SLOW
#OBJS = locore.o main.o rcc.o startup.o gpio.o usart.o random.o prf.o delay.o SLOW
#OBJS = locore.o main.o rcc.o gpio.o usart.o random.o prf.o startup.o delay.o SLOW
#OBJS = locore.o main.o rcc.o gpio.o usart.o random.o delay.o startup.o prf.o SLOW
OBJS = locore.o main.o rcc.o gpio.o usart.o random.o delay.o startup.o prf.o

#OBJS = delay.o locore.o main.o gpio.o rcc.o usart.o random.o prf.o FAST
#OBJS = locore.o delay.o main.o gpio.o rcc.o usart.o random.o prf.o FAST
#OBJS = locore.o delay.o rcc.o main.o gpio.o usart.o random.o prf.o FAST
#OBJS = locore.o delay.o rcc.o main.o gpio.o usart.o random.o prf.o startup.o FAST
#OBJS = locore.o rcc.o main.o gpio.o usart.o random.o prf.o delay.o FAST
#OBJS = locore.o main.o gpio.o rcc.o usart.o random.o prf.o delay.o FAST
#OBJS = locore.o prf.o rcc.o gpio.o usart.o random.o delay.o startup.o main.o FAST
#OBJS = locore.o prf.o rcc.o gpio.o usart.o random.o startup.o delay.o main.o FAST
#OBJS = locore.o prf.o rcc.o gpio.o usart.o startup.o random.o delay.o main.o FAST
#OBJS = locore.o prf.o gpio.o usart.o random.o delay.o main.o rcc.o startup.o FAST
#OBJS = locore.o prf.o gpio.o usart.o random.o delay.o main.o startup.o rcc.o FAST
#OBJS = locore.o startup.o prf.o gpio.o usart.o random.o delay.o main.o rcc.o FAST
#OBJS = locore.o startup.o prf.o gpio.o usart.o random.o delay.o main.o rcc.o

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

#OCDCFG = -f /usr/share/openocd/scripts/board/stm32h747i-disco.cfg
OCDCFG = -f board/stm32h747i-disco.cfg

flash:  print.elf
	#openocd $(OCDCFG) -c "program print.elf verify reset" -c "exit"
	#openocd $(OCDCFG) -c "program print.elf verify reset"
	openocd $(OCDCFG) -c "program print.elf verify reset exit"

# Not tested, but this might work ..
burnit:
	openocd $(OCDCFG) -c "init" -c "flash write_image erase print.bin 0x08000000" -c "exit"

# Also not tested
burnit2:
	st-flash write print.bin 0x08000000

clean:
	rm -f *.o print.elf print.bin print.dump
