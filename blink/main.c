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

#define TWICE

void
startup ( void )
{
	rcc_init ();

	led_init ();

	for ( ;; ) {
	    led_on ();
	    delay ();
	    led_off ();
	    delay ();
#ifdef TWICE
	    led_on ();
	    delay ();
	    led_off ();
	    delay ();
	    delay ();
	    delay ();
#endif
	}
}

/* THE END */
