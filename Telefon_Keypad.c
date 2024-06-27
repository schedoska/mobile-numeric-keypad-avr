#include "Telefon_Keypad.h"

uint8_t KeypadSlownik[16] = {EMPTY_1, ABC_2, DEF_3, DELETE,
							GHI_4, JKL_5, MNO_6, CLEAR,
							PQRS_7, TUV_8, WXYZ_9, NOTHING,
							STAR_0, SPACE, HASH, NOTHING};

uint8_t TableSizes[15] 	= {0, 1, 4, 4, 4, 4, 4, 5, 4, 5, 2, 1, 1, 0, 0};

char Tab_EMPTY_1[1] 	= {'1'};
char Tab_ABC_2[4] 		= {'a','b','c','2'};
char Tab_DEF_3[4] 		= {'d','e','f','3'};
char Tab_GHI_4[4] 		= {'g','h','i','4'};
char Tab_JKL_5[4] 		= {'j','k','l','5'};
char Tab_MNO_6[4] 		= {'m','n','o','6'};
char tab_PQRS_7[5] 		= {'p','q','r','s','7'};
char Tab_TUV_8[4] 		= {'t','u','v','8'};
char Tab_WXYZ_9[5] 		= {'w','x','y','z','9'};
char Tab_STAR_0[2] 		= {'*','0'};
char Tab_SPACE[1] 		= {' '};
char Tab_HASH[1] 		= {'#'};

uint8_t TranslateToPhoneKey(uint8_t KeyPad)
{
	if(KeyPad <= 0 || KeyPad > 15) return NOTHING;
	return KeypadSlownik[KeyPad - 1];
}

uint8_t GetPhoneKeySize(uint8_t PhoneKey)
{
	if(PhoneKey < 0 || PhoneKey > 14) return 0;
	return TableSizes[PhoneKey];
}

uint8_t isSpecialFunction(uint8_t PhoneKey)
{
	if(PhoneKey > 0 && PhoneKey < 13) return 0;
	else return 1;
}

char GetCharFromClick(uint8_t PhoneKey, int TimesClicked)
{
	TimesClicked--;
	switch(PhoneKey)
	{
	case EMPTY_1:
		return Tab_EMPTY_1	[TimesClicked % TableSizes[EMPTY_1]];
	case ABC_2:
		return Tab_ABC_2	[TimesClicked % TableSizes[ABC_2]];
	case DEF_3:
		return Tab_DEF_3	[TimesClicked % TableSizes[DEF_3]];
	case GHI_4:
		return Tab_GHI_4	[TimesClicked % TableSizes[GHI_4]];
	case JKL_5:
		return Tab_JKL_5	[TimesClicked % TableSizes[JKL_5]];
	case MNO_6:
		return Tab_MNO_6	[TimesClicked % TableSizes[MNO_6]];
	case PQRS_7:
		return tab_PQRS_7	[TimesClicked % TableSizes[PQRS_7]];
	case TUV_8:
		return Tab_TUV_8	[TimesClicked % TableSizes[TUV_8]];
	case WXYZ_9:
		return Tab_WXYZ_9	[TimesClicked % TableSizes[WXYZ_9]];
	case STAR_0:
		return Tab_STAR_0	[TimesClicked % TableSizes[STAR_0]];
	case SPACE:
		return Tab_SPACE	[TimesClicked % TableSizes[SPACE]];
	case HASH:
		return Tab_HASH		[TimesClicked % TableSizes[HASH]];
	default:
		return '$';
	}
}

void GetTextPart(char Text[], char PartText[], int From, int To)
{
	for(int q = From; q < To; q++)
	{
		PartText[q - From] = Text [q];
	}
}

















