/* main.c
 * (c) Tom Trebisky  12-20-2023
 * First worked 1-11-2024
 */

#include "stdint.h"
#include "protos.h"

#ifdef notdef
/* This gives a blink rate of about 2 Hz
 * (it really does!)
 */
#define FAST	500

#define FASTER	50
#define SLOWER	400

/* I use delay_count along with gdb to check this timing
 * I see about 22 counts per second using 1000 in
 * the following.  So 10000 should yield 2.2 counts
 * and 20,000 should yield 1 count.  Maybe.
 */

void
delay ( void )
{
	// volatile int count = 1000 * FAST;
	volatile int count = 20000 * FAST;

	while ( count-- )
	    ;
}
#endif

/* This is weird.  A single delay yields very fast blinking,
 * but two becomes absurdly slow.
 * I fixed this by adding an argument to delay()
 * Then more weird stuff and I had to bump argument to
 * 25 to get the blink rate under control.
 * Very strange mysteries with delay() XXX
 * 10-4-2026
 */
static void
led_tick ( void )
{
	led_on ();
	//delay ();
	delay ( 25 );
	led_off ();
	delay ( 25 );
	//delay ();
}

void
led_spin ( int msg )
{
	if ( msg )
	    printf ( "Spinning\n" );

	for ( ;; ) {
	    led_tick ();
	}
}

/* test LED blink */
void
test1 ( void )
{
	led_spin ( 0 );
}

/* test serial output */
void
test2 ( void )
{
	int mode = 0;
	int count = 0;

	for ( ;; ) {

	    // uart_putc ( 'R' );
	    if ( mode ) {
			count++;
			printf ( "Game over, insert cash %d\n", count  );
			mode = 0;
	    } else {
			uart_puts ( "Game over, insert coin\n"  );
			mode = 1;
	    }

	    led_tick ();
	}
}

/* test random numbers */
void
test3 ( void )
{
	u32 ran;
	int n = 20;

	// for ( ;; ) {
	while ( n-- ) {
	    ran = random_next ();
	    printf ( "Random: %8x %d\n", ran, ran );

	    led_tick ();
	}

	led_spin ( 1 );
}

/* test random numbers */
#define LIMIT	(256*10000)

void
test4 ( void )
{
	u32 ran;
	int i;
	u32 bins[256];
	int r;

	for ( i=0; i<256; i++ )
	    bins[i] = 0;

	for ( i=0; i<LIMIT; i++ ) {
	    ran = random_next ();
	    r = ran & 0xff;
	    bins[r]++;
	    r = ran>>8 & 0xff;
	    bins[r]++;
	    r = ran>>16 & 0xff;
	    bins[r]++;
	    r = ran>>24 & 0xff;
	    bins[r]++;
	}

	for ( i=0; i<256; i++ )
	    printf ( "%d:  %d\n", i, bins[i] );

	led_spin ( 1 );
}

int xbins[10];

void
test_bss ( void )
{
	int i;

	for ( i=0; i<10; i++ )
	    printf ( "bin %d = %08x\n", i, xbins[i] );
}

/* Nice, but no LED action */
void
idle ( void )
{
	printf ( "Idle (spinning)\n" );

    for ( ;; ) {
        /*
        irq_disable ();
        asm volatile( "wfe" );
        irq_enable ();
        */
        asm volatile( "wfi" );
    }
}

void
startup ( void )
{
	// mem_init ();

	rcc_init ();

	gpio_init ();
	led_init ();
	uart_init ();
	random_init ();

	uart_puts ( " -- Reset\n"  );
	uart_show ();

	// test_bss ();
	// test1 ();
	// test2 ();
	test3 ();
	// test4 ();

	idle ();
}

/* THE END */
