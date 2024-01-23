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
#define CR1_TX_ENA		BIT(3)
#define CR1_RX_ENA		BIT(2)
#define CR1_UART_ENA		BIT(0)

// XXX - alt function pins

/* RCC sets up the peripheral clock at 60 Mhz
 */
#define		PCLK	60000000

#define BAUD	115200


/* The USART can be used in either FIFO enabled or disabled mode
 * We use it in the simplest possible mode.
 * No fifo, no interrupts.
 * Note that the HAL driver in CubeMX is over 4700 lines of code
 *  to support the myriad of options possible with the usart.
 */

void
uart_init ( void )
{
	struct usart *up = UART1_BASE;
	u32 val;
	u32 div;

	gpio_uart1_pins ();

	up->cr1 = CR1_RX_ENA | CR1_TX_ENA;

	div = BAUD * 2;
	val = PCLK + div / 2;
	val /= div;
	up->brr = val;

	up->cr1 |= CR1_UART_ENA;
}

#define ISR_TXE	BIT(7)

void
uart_putc ( int c )
{
	struct usart *up = UART1_BASE;

	while ( ! (up->isr & ISR_TXE) )
	    ;

	up->tdr = c;
}

void
uart_puts ( char *s )
{
	int cc;

	while ( cc = *s++ ) {
	    if ( cc == '\n' )
		uart_putc ( '\r' );
	    uart_putc ( cc );
	}
}

/* THE END */
