/* protos.h
 * (c) Tom Trebisky  12-20-2023
 */

void led_init ( void );
void led_on ( void );
void led_off ( void );

typedef unsigned int u32;
typedef volatile unsigned int vu32;

#define BIT(x)	(1<<(x))

/* THE END */
