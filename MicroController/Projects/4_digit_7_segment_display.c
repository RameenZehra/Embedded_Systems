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
		unsigned char codes[] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x2, 0x78, 0x0, 0x10};
		unsigned short counter = 0;
	/* configure and enable external interrupt 1 */
	config_edge_triggered(EXTERNAL_INTERRUPT_0);
	enable_interrupt(EXTERNAL_INTERRUPT_0);

	/* configure and enable external interrupt 2 */
	config_edge_triggered(EXTERNAL_INTERRUPT_1);
	enable_interrupt(EXTERNAL_INTERRUPT_1);
	//P2 = codes[0];
	while (1)
	{
		unsigned char i;
		unsigned char first = 0;
		unsigned char tenth = 0;
		unsigned char hundredth = 0;
		unsigned char thousandth = 0;
		
		for (i = 0; i < 20; i++)
		{
			timer_delay_using_starting_point(FIFTY_MS_STARTING_POINT);
		}
		//if (started == 1)
		{
			first = counter % 10;
			tenth = counter / 10;
			if (tenth >= 10)
			{
				hundredth = tenth / 10;
				tenth = tenth % 10;
			}
			if (hundredth >= 10)
			{
				thousandth = hundredth / 10;
				hundredth = hundredth % 10;
			}
			P1 = 1;
			P2 = codes[first];
			P1 = 2;
			P2 = codes[tenth];
//			P1 = 4;
//			P2 = codes[hundredth];
//			P1 = 8;
//			P2 = codes[thousandth];
			counter += 1;
		}
	}
}