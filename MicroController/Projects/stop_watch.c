#include <REG51.h>

#define FIFTY_MS_STARTING_POINT	15535
#define EXTERNAL_INTERRUPT_0	0
#define EXTERNAL_INTERRUPT_1	2
unsigned char started = 0;

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

void start_stop_ISR() interrupt EXTERNAL_INTERRUPT_0
{
	started = started ^ 1;
}

void reset_ISR() interrupt EXTERNAL_INTERRUPT_1
{
	if (started == 0)
	{
		P2 = 0;
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
	
	P2 = 0;
	while (1)
	{
		unsigned char i;
		for (i = 0; i < 20; i++)
		{
			timer_delay_using_starting_point(FIFTY_MS_STARTING_POINT);
		}
		if (started == 1)
		{
			P2 += 1;
		}
	}
}