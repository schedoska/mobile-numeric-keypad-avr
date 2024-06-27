#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include "getkey.h"

/*int main()
{
	DDRD = 0xff;

	DDRC = 0b11110000;
	PORTC = 0xFF;

	while(1)
	{
		//PORTD = ~(PINC & 0b00001111);
		//PORTD = getchar4(2);
		PORTD = getchar16();
	}
}*/

uint8_t Clikced_Before = 0;

int getchar4(int Row)
	{
	// Row 0 - 1 i 3 - 4
	PORTC |= 0b11110000;
	PORTC &= ~(1 << (Row + 4));

	for(int q = 0; q < 4; q++)
	{
		if((~PINC) & (1<<q))
		{
			return q + 1;
		}
	}

	PORTC |= 0b11110000;
	return 0;
}

int getchar16()
{
	for(int q = 0; q < 4; q++)
	{
		int Liczba = getchar4(q);
		if(Liczba > 0)
			return Liczba + q * 4;
	}
	return 0;
}

int getchar16_debounced()
{
	uint8_t Clicked_Now = getchar16();
	if(Clikced_Before == 0)
	{
		Clikced_Before = Clicked_Now;
		return Clicked_Now;
	}
	Clikced_Before = Clicked_Now;
	return 0;
}

void KeyPad_init()
{
	DDRD = 0xff;

	DDRC = 0b11110000;
	PORTC = 0xFF;
}







