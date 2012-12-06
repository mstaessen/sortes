#include "general.h"
#include "lcd.h"
#include "LCDBlocking.h"

#define MAX_LENGTH 16

void LCD_show(int pos, char *str, int length) {
	int max = MAX_LENGTH - pos;

	char *cur = &LCDText[0] + pos;
	int i;
	if (length > max) length = max;
	for(i = 0; i < length; i++) {
		*cur++ = *str++;
	}

	if (cur != &LCDText[MAX_LENGTH]) {
		*cur = '\0';
	}

	LCDUpdate();
}
