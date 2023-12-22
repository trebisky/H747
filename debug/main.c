/* main.c
 * (c) Tom Trebisky  12-20-2023
 */

#include "protos.h"

/* This gives a blink rate of about 2.7 Hz */
/* i.e. the delay time is about 0.2 seconds (200 ms) */
#define FAST	200

#define FASTER	50
#define SLOWER	400

void
delay ( void )
{
	volatile int count = 1000 * FAST;

	while ( count-- )
	    ;
}

#define RAM_BASE	0x24000000
#define RAM_SIZE	0x80000
#define RAM_END		0x24080000

int i;

void
loaf ( void )
{
	u32 *p;

	p = (u32 *) RAM_BASE;

	*p++ = 0xaaaa5555;
	*p = 0xaaaa5555;

	i = 0;

	for ( ;; ) {
	    delay ();
	    *p = i++;
	}
}

void
startup ( void )
{
	u32 *p, *ep;

	p = (u32 *) RAM_BASE;
	ep = (u32 *) RAM_END;

	while ( p < ep ) {
	    *p++ = 0xdeadbeef;
	}

	loaf ();
}

/* THE END */
