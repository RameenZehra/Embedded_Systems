#include <REG51.h>

void ext0_interrupt() interrupt 0
{
   P2 += 1;
}

void ext1_interrupt(void) interrupt 2
{
   P2 = 0;
}
int main()
{
   TCON = TCON | 5;
   P2 = 0;
   IE = 0x85;
	 IP = 0x4;
   while(1); //what happens when this is commented ??? program doesn't work as expected. why?
}
