/* main.c
 * (c) Tom Trebisky  12-20-2023
 */

#include "protos.h"

/* This gives a blink rate of about 2.7 Hz */
/* i.e. the delay time is about 0.2 seconds (200 ms) */
#define FAST	200

#define FASTER	50
#define SLOWER	400

/* I use delay_count along with gdb to check this timing
 * I see about 22 counts per second using 1000 in
 * the following.  So 10000 should yield 2.2 counts
 * and 20,000 should yield 1 count.
 */

void
delay ( void )
{
	// volatile int count = 1000 * FAST;
	volatile int count = 20000 * FAST;

	while ( count-- )
	    ;
}

// #define TWICE

volatile int delay_count;

/* Handy place to set a breakpoint */
void
next_count ( void )
{
}

void
startup ( void )
{
	delay_count = 0;

	rcc_init ();

	led_init ();
	usart_init ();

	for ( ;; ) {
	    delay_count++;

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
