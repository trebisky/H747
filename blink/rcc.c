/* rcc.c
 * (c) Tom Trebisky  12-20-2023
 */

#include "protos.h"

static void pwr_init ( void );

/* RCC (reset and clock control
 * 0x58024400 - 0x580247FF (RM page 138)
 * RM section 9 (page 351)
 * PWR in section 7
 */

#define RCC_BASE	0x58024400
#define PWR_BASE	0x58024800

// RCC_AHB4ENR is at offset 0xE0
// I am cheating with the following
// #define RCC_EN_BASE	0x580244E0

/* RCC registers are in 4 sections with banking and rules
 * about access from CPU1 or CPU2
 */
struct rcc {
	vu32	cr;		/* 00 */
	vu32	hsicfgr;	/* 04 */
	vu32	crrcr;		/* 08 */
	vu32	csicfgr;	/* 0c */
	vu32	cfgr;		/* 10 */
	u32	_pad0;
	vu32	d1cfgr;		/* 18 */
	vu32	d2cfgr;		/* 1c */
	vu32	d3cfgr;		/* 20 */
	u32	_pad1;
	vu32	pllckselr;	/* 28 */
	vu32	pllcfgr;	/* 2c */
	vu32	pll1divr;	/* 30 */
	vu32	pll1fracr;	/* 34 */
	vu32	pll2divr;	/* 38 */
	vu32	pll2fracr;	/* 3c */
	vu32	pll3divr;	/* 40 */
	vu32	pll3fracr;	/* 44 */
	u32	_pad2;
	vu32	d1ccipr;	/* 4c */
	vu32	d2ccipr;	/* 50 */
	vu32	d2ccip2r;	/* 54 */
	vu32	d3ccipr;	/* 58 */
	u32	_pad3;
	vu32	cier;		/* 60 */
	vu32	cifr;		/* 64 */
	vu32	cicr;		/* 68 */
	u32	_pad4;
	vu32	bdcr;		/* 70 */
	vu32	csr;		/* 74 */
	u32	_pad5;
	vu32	ahb3rstr;	/* 7c */
	vu32	ahb1rstr;	/* 80 */
	vu32	ahb2rstr;	/* 84 */
	vu32	ahb4rstr;	/* 88 */
	vu32	apb3rstr;	/* 8c */
	vu32	apb1lrstr;	/* 90 */
	vu32	apb1hrstr;	/* 94 */
	vu32	apb2rstr;	/* 98 */
	vu32	apb4rstr;	/* 9c */
	vu32	gcr;		/* a0 */
	u32	_pad6;
	vu32	d3amr;		/* a8 */
	u32	_pad7[9];
	vu32	rsr;		/* d0 (aliases) */
	vu32	ahb3enr;	/* d4 (aliases) */
	vu32	ahb1enr;	/* d8 (aliases) */
	vu32	ahb2enr;	/* dc (aliases) */
	vu32	ahb4enr;	/* E0 (aliases) */
	vu32	apb3enr;	/* E4 (aliases) */
	vu32	apb1lenr;	/* E8 (aliases) */
	vu32	apb1henr;	/* Ec (aliases) */
	vu32	apb2enr;	/* F0 (aliases) */
	vu32	apb4enr;	/* F4 (aliases) */
	u32	_pad8;
	vu32	ahb3lpenr;	/* Fc (aliases) */
	vu32	ahb1lpenr;	/* 100 (aliases) */
	vu32	ahb2lpenr;	/* 104 (aliases) */
	vu32	ahb4lpenr;	/* 108 (aliases) */
	vu32	apb3lpenr;	/* 10c (aliases) */
	vu32	apb1llpenr;	/* 110 (aliases) */
	vu32	apb1hlpenr;	/* 114 (aliases) */
	vu32	apb2lpenr;	/* 118 (aliases) */
	vu32	apb4lpenr;	/* 11c (aliases) */
};

#define GPIO_ALL_ENA	0x7ff
#define GPIO_I_ENA	BIT(8)

void
rcc_init ( void )
{
	struct rcc *rp;

	pwr_init ();

	rp = (struct rcc *) RCC_BASE;

	/* turn on all GPIO */
	// rp->ahb4enr |= GPIO_I_ENA;
	rp->ahb4enr |= GPIO_ALL_ENA;
}

/* ===================================================== */
/* ===================================================== */

struct pwr {
	vu32	cr1;
	vu32	csr1;
	vu32	cr2;
	vu32	cr3;
	vu32	cpu1cr;	/* 0x10 */
	vu32	cpu2cr;
	vu32	d3cr;
	u32	_pad0;
	vu32	wkupcr;	/* 0x20 */
	vu32	wkupfr;
	vu32	wkupepr;
};

/* default (reset) state of cr3 is 0x6
 * which enables both SMPS and LDO
 */
#define CR3_SDEN	BIT(2)
#define CR3_LDOEN	BIT(1)

static void
pwr_init ( void )
{
	/* smps is already enabled, nothing to do */
}

/* THE END */
