#include <REG51.h>

#define START_FROM	32768
#define STEPS_IN_MICRO_SEC	5000
#define EXTERNAL_INTERRUPT_0	0
#define EXTERNAL_INTERRUPT_1	2
#define TIMER_MAX_VALUE 62768
#define TIMER_MIN_VALUE 2768

unsigned short on_timer_starting_point = START_FROM;
unsigned short off_timer_starting_point = START_FROM;

void config_edge_triggered(unsigned char interrupt_num)
{
	if (interrupt_num == EXTERNAL_INTERRUPT_0)
	{
		TCON |= 1;
	}
	if (interrupt_num == EXTERNAL_INTERRUPT_1)
	{
		TCON |= 4;
	}
}

void enable_interrupt(unsigned char interrupt_num)
{
	IE = IE | (1 << 7) | (1 << interrupt_num);
}

void decrease_ISR() interrupt EXTERNAL_INTERRUPT_0
{
	if (on_timer_starting_point < TIMER_MAX_VALUE && off_timer_starting_point > TIMER_MIN_VALUE)
	{
		on_timer_starting_point += STEPS_IN_MICRO_SEC;
		off_timer_starting_point -= STEPS_IN_MICRO_SEC;
	}
}

void increase_ISR() interrupt EXTERNAL_INTERRUPT_1
{
	if (on_timer_starting_point > TIMER_MIN_VALUE && off_timer_starting_point < TIMER_MAX_VALUE)
	{
		on_timer_starting_point -= STEPS_IN_MICRO_SEC;
		off_timer_starting_point += STEPS_IN_MICRO_SEC;
	}
}

void timer_delay_using_starting_point(unsigned short starting_point)
{
		TMOD = 1;
		TL0 = starting_point & 0xff;
		TH0 = starting_point >> 8;
		TR0 = 1;
		while (TF0 == 0);
		TR0 = 0;
		TF0 = 0;
}

void main()
{
	/* configure and enable external interrupt 1 */
	config_edge_triggered(EXTERNAL_INTERRUPT_0);
	enable_interrupt(EXTERNAL_INTERRUPT_0);
	
	/* configure and enable external interrupt 2 */
	config_edge_triggered(EXTERNAL_INTERRUPT_1);
	enable_interrupt(EXTERNAL_INTERRUPT_1);

	while (1)
	{
		/* Generate pulse */
		P2 = P2 | 1;
		timer_delay_using_starting_point(on_timer_starting_point);
		P2 = P2 & 0xFE;
		timer_delay_using_starting_point(off_timer_starting_point);
	}
}