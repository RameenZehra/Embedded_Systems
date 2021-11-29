#include <REG51.h>

#define FIFTY_MS_STARTING_POINT	0
#define TIMER_0_INTERRUPT	1

void timer0_overflow_ISR() interrupt TIMER_0_INTERRUPT
{
	//TR0 = 0;
	TF0 = 0;
}

void main()
{
	unsigned char i= 0;
	unsigned char j = 10;


	TMOD = 1;
	TF0 = 0;
	//TL0 = FIFTY_MS_STARTING_POINT & 0xff;
	//TH0 = FIFTY_MS_STARTING_POINT >> 8;
	IE = IE | (1 << 7) | (1 << TIMER_0_INTERRUPT);
	//TR0 = 1;
	
	j = j / i;
	if (PSW & (1 << 2))
	{
		TF0 = 1;
	}
	
	
	while (1)
	{
		j = j + 1;
	}
}
