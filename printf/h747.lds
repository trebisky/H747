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
   sram(WAIL) : ORIGIN = 0x30000000, LENGTH = 288K
}

SECTIONS
{
   .text :
   {
       *(.vectors*)
       *(.text*)
       . = ALIGN(4);
       __text_end = .;
       _etext = .;
   } > flash

   .bss  :
   {
       . = ALIGN(4);
       __bss_start = .;
       *(.bss*)
       *(COMMON)
       . = ALIGN(4);
       __bss_end = .;
   } > sram

   .data :
   {
       . = ALIGN(4);
       __data_start = .;
       *(.data*)
       . = ALIGN(4);
       __data_end = .;
   } > sram AT> flash

   .rodata :
   {
       . = ALIGN(4);
       *(.rodata*)
       . = ALIGN(4);
   } > flash
}
