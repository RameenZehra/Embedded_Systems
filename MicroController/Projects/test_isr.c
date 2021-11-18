#include <REG51.h>

void interrupt0_ISR() interrupt 0 // external interrupt 1
{
   P2 += 1;
}

void  interrupt2_ISR(void) interrupt 2 // external interrupt 2
{
   P2 = 0;
}

void main()
{
   TCON = TCON | 5;
   P2 = 0;
   IE = 0x85;
   while(1); //what happens when this is commented ??? program doesn't work as expected. why?
}

 
