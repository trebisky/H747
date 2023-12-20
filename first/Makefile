# Makefile for the first H747 demo
#
# No actual code here, we are just using openocd
# to poke at the board.
#
#  Tom Trebisky  12-20-2023

# The interface is specified as part of the board file, so we don't need
# to specify it.
#OCDCFG = -f /usr/share/openocd/scripts/interface/stlink.cfg -f /usr/share/openocd/scripts/board/stm32h747i-disco.cfg
OCDCFG = -f /usr/share/openocd/scripts/board/stm32h747i-disco.cfg

# To use openocd interactively, you want to use two windows.
# In the first one type "make ocd" to run ocd
# In the second one type "telnet localhost 4444"
# Use the second one to type interactive commands.
# The second one need not be in the same directory as "make ocd" was started in.
# Any files read or written should be in the same directory openocd was started in.
ocd:
	openocd $(OCDCFG)

banks:
	openocd $(OCDCFG) -c "init" -c "flash banks" -c "exit"

list:
	openocd $(OCDCFG) -c "init" -c "flash list" -c "exit"

bank0.bin:
	openocd $(OCDCFG) -c "init" -c "flash read_bank 0 bank0.bin 0 0x100000" -c "exit"

bank1.bin:
	openocd $(OCDCFG) -c "init" -c "flash read_bank 1 bank1.bin 0 0x100000" -c "exit"

# With a brand new board, the contents of both bank0 and bank1 are all 0xff
# i.e. there is nothing there, the board/chip has never been programmed.

# Not tested, but this might work ..
burnit:
	openocd $(OCDCFG) -c "init" -c "flash write_image erase blink.bin 0x08000000" -c "exit"

# Also not tested
burnit2:
	st-flash write blink.bin 0x8000000
	openocd $(OCDCFG) -c "program blink.elf verify reset exit"

clean:
	rm -f *.bin

# THE END
