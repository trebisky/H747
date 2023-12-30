/* main.c
 * (c) Tom Trebisky  12-20-2023
 *
 * This is all about experimenting with openocd to see
 * if we can learn how to use openocd to monitor a
 * simple C program.  Indeed we can!
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

int result;

void
addem ( int a, int b )
{
	result = a + b;
}

void
startup ( void )
{
	addem ( 2, 2 );
	addem ( 2, 3 );
}

void
xstartup ( void )
{
	u32 *p, *ep;

	for ( ;; ) ;

	p = (u32 *) RAM_BASE;
	ep = (u32 *) RAM_END;

	while ( p < ep ) {
	    *p++ = 0xdeadbeef;
	}

	loaf ();
}

/* THE END */
