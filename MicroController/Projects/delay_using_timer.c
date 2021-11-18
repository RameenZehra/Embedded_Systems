#include <REG51.h>
void main()
{
	while (1)
	{
		TMOD = 1;
		TL0 = 0;
		TH0 = 0;
		P2 = P2 ^ 1; // Toggle first bit of P2 using XOR
		TR0 = 1;
		while (TF0 == 0);
		TR0 = 0;
		TF0 = 0;
	}
}