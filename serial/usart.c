/* usart.c
 * (c) Tom Trebisky  1-8-2024
 *
 * USART driver for the STM32H747
 * 
 * see RM0399 page 2194 section 51
 * (also page 141 for addresses)
 */

#include "protos.h"

/* The H747 has 8 usart devices (1-8)
 * devices 1 and 6 are on the APBx
 * devices 2,3,4,5, 7,8  are on the APBx
 *
 * There is also an LPUSART
 */

#define UART1_BASE	(struct usart *) 0x40011000
#define UART2_BASE	(struct usart *) 0x40004400
#define UART3_BASE	(struct usart *) 0x40004800
#define UART4_BASE	(struct usart *) 0x40004c00
#define UART5_BASE	(struct usart *) 0x40005000
#define UART6_BASE	(struct usart *) 0x40011400
#define UART7_BASE	(struct usart *) 0x40007800
#define UART8_BASE	(struct usart *) 0x40007c00

struct usart {
	vu32	cr1;		/* 00 */
	vu32	cr2;		/* 04 */
	vu32	cr3;		/* 08 */
	vu32	brr;		/* 0c */
	vu32	gtpr;		/* 10 */
	vu32	rtor;		/* 14 */
	vu32	rqr;		/* 18 */
	vu32	isr;		/* 1c */
	vu32	icr;		/* 20 */
	vu32	rdr;		/* 24 */
	vu32	tdr;		/* 28 */
	vu32	presc;		/* 2c */
};

#define CR1_FIFO_ENA		BIT(29)

// XXX - alt function pins

/* The USART can be used in either FIFO enabled or disabled mode
 */

void
usart_init ( void )
{
}

/* THE END */
