#include "general.h"

#include "LCDBlocking.h"
#include "lcd.h"

void main() {
	// Init LCD screen
	LCDInit();

	LCD_show(0, "Hello, world!", 13);
    
    while(1) {
        // NOP
    }
}
