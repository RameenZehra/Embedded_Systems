#include <REG51.h>

#define START_FROM	127
#define EXTERNAL_INTERRUPT_0	0
#define EXTERNAL_INTERRUPT_1	2

unsigned char on_start_from = START_FROM;
unsigned char off_start_from = START_FROM;

void config_edge_triggered(unsigned char interrupt_num)
{
	if (interrupt_num == 0)
	{
		TCON |= 1;
	}
	if (interrupt_num == 2)
	{
		TCON |= 4;
	}
}

void enable_interrupt(unsigned char interrupt_num)
{
	IE = IE | (1 << 7) | (1 << interrupt_num);
}


void decrease_ISR() interrupt 0
{
	if (on_start_from < 247 && off_start_from > 7)
	{
		on_start_from += 10; // on_start_from = on_start_from + 25;
		off_start_from -= 10;
	}
}
void increase_ISR() interrupt 2
{
	if (on_start_from > 7 && off_start_from < 247)
	{
		on_start_from -= 10; // on_start_from = on_start_from + 25;
		off_start_from += 10;
	}
}

void main()
{
	config_edge_triggered(EXTERNAL_INTERRUPT_0);
	enable_interrupt(EXTERNAL_INTERRUPT_0);
	
	config_edge_triggered(EXTERNAL_INTERRUPT_1);
	enable_interrupt(EXTERNAL_INTERRUPT_1);

	TMOD = 3;
	while (1)
	{
		TL0 = on_start_from;
		P2 = P2 | 1; 
		TR0 = 1;
		while (TF0 == 0);
		TR0 = 0;
		TF0 = 0;
		
		TL0 = off_start_from;
		P2 = P2 & 0xFE;
		TR0 = 1;
		while (TF0 == 0);
		TR0 = 0;
		TF0 = 0;
	}
}