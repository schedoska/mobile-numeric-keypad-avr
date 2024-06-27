#ifndef TELEFON_KEYPAD_H_
#define TELEFON_KEYPAD_H_
#include <avr/io.h>

#define NOTHING 	0
#define EMPTY_1 	1
#define ABC_2 		2
#define DEF_3 		3
#define GHI_4 		4
#define JKL_5 		5
#define MNO_6 		6
#define PQRS_7 		7
#define TUV_8 		8
#define WXYZ_9 		9
#define STAR_0 		10
#define SPACE 		11
#define HASH 		12
#define DELETE 		13
#define CLEAR 		14

uint8_t TableSizes[15];

uint8_t TranslateToPhoneKey(uint8_t KeyPad);
uint8_t GetPhoneKeySize(uint8_t PhoneKey);
uint8_t isSpecialFunction(uint8_t PhoneKey);
char 	GetCharFromClick(uint8_t PhoneKey, int TimesClicked);

void GetTextPart(char Text[], char PartText[], int From, int To);

#define MIGANIE_KURSORA_TIME 	4
#define KEY_SCREEN_REFRESH 		100
#define ONE_CHAR_TIME 			17000

#endif /* TELEFON_KEYPAD_H_ */
