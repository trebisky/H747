/* blink.lds
 * linker script for STM32H747
 *
 * Memory layout on my STM32H747 discovery is like so:
 *
 * 0x08000000 - 0x080fffff - Flash bank 0 (1M)
 * 0x08100000 - 0x081fffff - Flash bank 1 (1M)
 * 0x24000000 - 0x2407ffff - AXI SRAM (512K)
 * 0x30000000 - 0x30047fff - SRAM (256K + 32K)
 */
MEMORY
{
   flash(RX)  : ORIGIN = 0x08000000, LENGTH = 128K
   sram(WAIL) : ORIGIN = 0x24000000, LENGTH = 512K
}

SECTIONS
{
   .text : {
       *(.vectors*)
       *(.text*)
   } > flash
   .bss  : { *(.bss*) } > sram
}
