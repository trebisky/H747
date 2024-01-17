/* gpio.c
 * (c) Tom Trebisky  12-20-2023
 */

#include "protos.h"

void gpio_init ( void );
void gpio_sr ( u32 );

#define LED_PATTERN1	0x5000	// 0101
#define LED_PATTERN2	0xa000	// 1010

u32 led_patx, led_paty;

void
led_init ( void )
{
	gpio_init ();

	/* The idea is to blink 2 sets in alternation */
	led_patx = LED_PATTERN1 << 16 | LED_PATTERN2;
	led_paty = LED_PATTERN2 << 16 | LED_PATTERN1;
}

void
led_on ( void )
{
	gpio_sr ( led_patx );
}

void
led_off ( void )
{
	gpio_sr ( led_paty );
}

/* The four LED are on Gpio "I" - 12,13,14,15
 *  PI12 -- led 1  - green
 *  PI13 -- led 2  - orange
 *  PI14 -- led 3  - red
 *  PI15 -- led 4  - blue
 *
 * pull down (open collector) to turn them on.
 *  (or just use push/pull)
 */

/* ----------------------------------------------------- */
/* ----------------------------------------------------- */
/* GPIO - we have a bunch (11) of these
 * RM section 12 (page 568)
 * Each gpio has 16 bits
 */

struct gpio {
	vu32	mode;		/* 0x00 */
	vu32	otype;		/* 0x04 */
	vu32	ospeed;		/* 0x08 */
	vu32	up_down;	/* 0x0c */
	vu32	in_data;	/* 0x10 */
	vu32	out_data;	/* 0x14 */
	vu32	set_reset;	/* 0x18 */
	vu32	lock;		/* 0x1c */
	vu32	alt_lo;		/* 0x20 */
	vu32	alt_hi;		/* 0x24 */
};

#define MODE_IN		0
#define MODE_OUT	1
#define MODE_ALT	2
#define MODE_ANA	3	// default

#define OT_PP		0	// default (push/pull)
#define OT_OD		1	// open drain

#define SPEED_LOW	0
#define SPEED_MED	1
#define SPEED_HI	2
#define SPEED_VHI	3

#define PULL_NONE	0
#define PULL_UP		1
#define PULL_DONW	2

/* The set/reset register has 16 reset controls in the
 *  high 16 bits and 16 set controls in the low 16 bits.
 *
 * The Alt function control has 4 bits per "bit",
 *  so "hi" has bits 15 - 8
 *  and "lo" has bits 7 - 0
 */

#define GPIO_A_BASE	0x58020000
#define GPIO_B_BASE	0x58020400
#define GPIO_C_BASE	0x58020800
#define GPIO_D_BASE	0x58020C00

#define GPIO_E_BASE	0x58021000
#define GPIO_F_BASE	0x58021400
#define GPIO_G_BASE	0x58021800
#define GPIO_H_BASE	0x58021C00

#define GPIO_I_BASE	0x58022000
#define GPIO_J_BASE	0x58022400
#define GPIO_K_BASE	0x58022800

static void
led_setup ( int bit )
{
	struct gpio *gp;
	u32 mask;
	u32 val;

	gp = (struct gpio *) GPIO_I_BASE;

	mask = 0x3 << bit*2;
	val = gp->mode & ~mask;
	val |= (MODE_OUT << bit*2);
	gp->mode = val;

	val = gp->otype & ~BIT(bit);
	val |= (OT_OD<bit);
	gp->otype = val;

	// low speed seems fine
	// no pull up/down seems fine
}

void
gpio_sr ( u32 val )
{
	struct gpio *gp = (struct gpio *) GPIO_I_BASE;

	gp->set_reset = val;
}

void
gpio_init ( void )
{
	led_setup ( 12 );
	led_setup ( 13 );
	led_setup ( 14 );
	led_setup ( 15 );
}

/* THE END */
