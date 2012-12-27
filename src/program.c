#include "time_input.h"
#include "sortes.h"
#include <stdlib.h>

Time currentTime, alarmTime;

bool wholeSecond;
unsigned int alarmTicks;

void tick() {
    wholeSecond = !wholeSecond;
    if (wholeSecond) {
        Time_tick(currentTime);
        outputTime(currentTime);
        
        if (Time_equals(currentTime, alarmTime)) {
            alarmTicks = 30;
        }
        
        if (alarmTicks > 0) {
            Led_setState(LED_ONE, true);
        }
    } else {
        if (alarmTicks > 0) {
            alarmTicks--;
            Led_setState(LED_ONE, false);
        }
    }
}

int main(void) {
    LCD_init();
    Led_init(LED_ONE);
    
    currentTime = inputTime("Set cur time:");
    if (currentTime == NULL) {
        LCD_setLine(LINE_ONE, "MemError");
        while (true);
        return 1;
    }
    alarmTime = inputTime("Set alarm time:");
    if (alarmTime == NULL) {
        LCD_setLine(LINE_ONE, "MemError");
        while (true);
        return 1;
    }
    
    LCD_clear();
    
    wholeSecond = true;
    Timer_setInterval(500, 500, tick);
    
    while (true);
    
	return 0;
}
