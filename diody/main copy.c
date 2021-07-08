#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <util/delay.h>
#include <avr/iom32.h>

#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif
#ifndef sbi
#define sbi(reg, bit) reg |= (_BV(bit))
#endif

#ifndef cbi
#define cbi(reg, bit) reg &= ~(_BV(bit))
#endif
// program napisany przez Dominię Arkabus 252839
int i, a;
//#zadanie na 3.0  - włączyć wszystkie diody LED
void zaswiecenie(int a)
{
	if (a == 1)
	{
		PORTD = 0xFF;
	}
	if (a == 2)
	{
		for (int i = 0; i < 8; i++)
		{
			sbi(PORTD, i);
		}
	}
	if (a == 3)
	{
		for (int i = 0; i < 8; i++)
		{
			PORTD |= (1 << i);
		}
	}
}
//#zadanie na 3.5 - mruganie wszystkimi diodami z częstotliwością 1s.
void mruganie()
{
	while (1)
	{
		PORTD = 0xFF;
		_delay_ms(1000);
		PORTD = 0x00;
		_delay_ms(1000);
	}
}
//#zadanie na 4.0 - biegający punkt
void bieganie()
{
	int k = 0;
	while (1)
	{
		while (k <= 6)
		{
			sbi(PORTD, k);
			_delay_ms(500);
			cbi(PORTD, k);
			_delay_ms(500);
			k++;
		}
		while (k >= 1)
		{
			sbi(PORTD, k);
			_delay_ms(500);
			cbi(PORTD, k);
			_delay_ms(500);
			k--;
		}
	}
}
//#zadanie na 4.5 - przycisk (swieci / nie swieci)
void przycisk_zaswiecenie()
{
	while (1)
	{
		if (bit_is_clear(PINC, PC0))
		{
			PORTD = 0xFF;
		}
		else
		{
			PORTD = 0x00;
		}
	}
}
int punkt_po_punkcie()
{
	if (bit_is_clear(PINC, PC1))
	{
		cbi(PORTD, i);
		if (i >= 7)
			a = i + 2;

		if (i <= 0)
			a = i - 2;

		if (i > a && i <= 7)
		{
			while (bit_is_clear(PINC, PC1))
				;
			a = i;
			i++;
		}
		if (i < a && i >= 0)
		{
			while (bit_is_clear(PINC, PC1))
				;
			a = i;
			i--;
		}
	}
	return i;
}
//#zadanie na 5.0
void dwa_przyciski()
{
	i = 0, a = -1;
	while (1)
	{
		while (bit_is_set(PINC, PC0) && bit_is_set(PINC, PC1))
			sbi(PORTD, i);
		while (bit_is_clear(PINC, PC0))
		{
			PORTD = 0xFF;
		}
		PORTD = 0x00;
		if (bit_is_clear(PINC, PC1))
		{
			i = punkt_po_punkcie();
		}
	}
}

int main()
{
	DDRD = 0xFF;
	cbi(DDRC, PC0);
	cbi(DDRC, PC1);
	sbi(PORTC, PC0);
	sbi(PORTC, PC1);

	zaswiecenie(1); //3.0
	// mruganie(); //3.5
	// bieganie(); //4.0
	// przycisk_zaswiecenie(); //4.5
	// dwa_przyciski(); //5.0
}
