Here it is!  My first code ever to run on the H747

This code doesn't do anything useful, but it does run
on the H747.  I am using this to teach myself how
to use openocd along with gdb
(specifically via gdb -tui)

I work in the following way:

1 - in one window I type "./ocd_start"
2 - in another window I type "telnet localhost 4444"
3 - in that telnet window I type "program debug.elf verify"
4 - in yet another window I type "./tui_start"

Then I can use the "tui" window to fool with gdb.
As an example, I do the following:

1 - list main.c:1
2 - b startup
3 - b addem
4 - continue
5 - disp result
6 - step

Note that "run" is not supported.  I continue to use step to watch
the program run and see the value of "result" change.
It all works just fine and setting breakpoints with the code
in flash works just fine somehow.

I don't yet have clocks set up, nor can I blink an LED,
nor can I use the virtual console.  But using openocd
and/or gdb I can see my program modifying variables and SRAM.
That does nicely to help me debug startup code.

This has already answered
several questions and taught me some things.
Many additional details will be found in comments in
the source files.
