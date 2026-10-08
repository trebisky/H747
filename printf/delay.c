/* delay.c
 * (c) Tom Trebisky  1-24-2023
 */

// #include "stdint.h"
#include "protos.h"

/* This gives a blink rate of about 2 Hz
 * (it really does!)
 */
#define FASTEST	500

#define FASTER	50
#define SLOWER	400

/* I use delay_count along with gdb to check this timing
 * I see about 22 counts per second using 1000 in
 * the following.  So 10000 should yield 2.2 counts
 * and 20,000 should yield 1 count.  Maybe.
 *
 * Note: 32 bit signed int is 2,147,483,647
 */

void
delay ( int ndelay )
{
	// volatile int count = 1000 * FAST;
	// volatile int count = 20000 * FAST;
	volatile int count = 20000 * FASTER * ndelay;

	while ( count-- )
	    ;
}

/* THE END */
