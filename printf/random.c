/* random.c
 * (c) Tom Trebisky  1-22-2024
 *
 * driver for the STM32H747 random number hardware
 *
 * Interestingly, the H747 includes hardware that generates
 * 32 bit true random numbers
 * 
 * see RM0399 page 1417 (section 36)
 * (also page 141 for addresses)
 */

#include "protos.h"

#define RAND_BASE	(struct random *) 0x48021800

struct random {
	vu32	cr;		/* 00 */
	vu32	status;		/* 04 */
	vu32	data;		/* 08 */
};

void
random_init ( void )
{
}

/* THE END */
