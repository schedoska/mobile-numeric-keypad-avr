#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include "HD44780.h"
#include "getkey.h"
#include "Telefon_Keypad.h"
#include <avr/interrupt.h>

char Text[32];
uint8_t Cursor_Pos = 0;
uint8_t Actual_Clicked = NOTHING;
uint8_t TimesClicked = 0;

uint8_t Miganie_Counter = 0;
uint8_t Miganie_State = 0;

void DeleteChar();
void Proceed_click(uint8_t PhoneKeyClicked);
void UpdateScreen();
void Timer_Restart();
void Timer_init();
void ClearTextSpace(char Text_space[], int Size);
void MoveNextPos();

int main()
{
	KeyPad_init();
	LCD_Initalize();
	Timer_init();

	while(1)
	{
		Proceed_click(TranslateToPhoneKey(getchar16_debounced()));
		UpdateScreen();
		_delay_ms(KEY_SCREEN_REFRESH);
	}
}

void Proceed_click(uint8_t PhoneKeyClicked)
{
	if(PhoneKeyClicked != NOTHING) Timer_Restart();
	else return;

	if(isSpecialFunction(PhoneKeyClicked))
	{
		if(PhoneKeyClicked == DELETE)
		{
			DeleteChar();
		}
		else if(PhoneKeyClicked == CLEAR)
		{
			ClearTextSpace(Text, 15);
		}
		return;
	}
	if(Actual_Clicked == PhoneKeyClicked)
	{
		TimesClicked++;
		Text[Cursor_Pos] = GetCharFromClick(PhoneKeyClicked, TimesClicked);
	}
	if(Actual_Clicked == NOTHING)
	{
		if(TableSizes[PhoneKeyClicked] == 1)
		{
			Text[Cursor_Pos] = GetCharFromClick(PhoneKeyClicked, TimesClicked);
			MoveNextPos();
			return;
		}
		Actual_Clicked = PhoneKeyClicked;
		TimesClicked = 1;
		Text[Cursor_Pos] = GetCharFromClick(PhoneKeyClicked, TimesClicked);
	}
	if(Actual_Clicked != NOTHING && Actual_Clicked != PhoneKeyClicked)
	{
		MoveNextPos();
		Actual_Clicked = PhoneKeyClicked;
		TimesClicked = 1;
		Text[Cursor_Pos] = GetCharFromClick(PhoneKeyClicked, TimesClicked);
	}
}

void UpdateScreen()
{
	LCD_Clear();
	Miganie_Counter++;

	if(Miganie_Counter > MIGANIE_KURSORA_TIME)
	{
		Miganie_Counter = 0;
		Miganie_State = !Miganie_State;
	}
	if(Actual_Clicked == NOTHING)
	{
		if(Miganie_State) Text[Cursor_Pos] = 0xFF;
		else Text[Cursor_Pos] = 160;
	}

	char TopText[16], BottomText[16];
	GetTextPart(Text, TopText, 0, 16);
	GetTextPart(Text, BottomText, 16, 31);

	LCD_WriteText(TopText);
	LCD_GoTo(0, 1);
	LCD_WriteText(BottomText);
}

void Timer_Restart()
{
	TCNT1 = 0;
}

void Timer_init()
{
	TCCR1B |= (1<<WGM12) | (1<<CS11) | (1<<CS10);
	OCR1A = ONE_CHAR_TIME;
	TCNT1 = 0;
	TIMSK |= (1<<OCIE1A);
	sei();
}

ISR (TIMER1_COMPA_vect)
{
	if(Actual_Clicked != NOTHING)
	{
		MoveNextPos();
	}
}

void MoveNextPos()
{
	Cursor_Pos++;
	Actual_Clicked = NOTHING;
	TimesClicked = 0;
}

void ClearTextSpace(char Text_space[], int Size)
{
	for(int q = 0; q < Size; q++)
	{
		Text_space[q] = ' ';
	}
	Cursor_Pos = -1;
	MoveNextPos();
}

void DeleteChar()
{
	if(Actual_Clicked == NOTHING)
	{
		Text[Cursor_Pos] = ' ';
		Cursor_Pos--;
		Actual_Clicked = NOTHING;
		TimesClicked = 0;
	}
	else
	{
		Text[Cursor_Pos] = ' ';
		Actual_Clicked = NOTHING;
		TimesClicked = 0;
	}
}




