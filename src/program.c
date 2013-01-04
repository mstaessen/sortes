#include "time_input.h"
#include "sortes.h"
#include <stdlib.h>
#include <malloc.h>

unsigned char _MALLOC_SPEC heap[256];

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
            Led_toggleState(LED_ONE);
        }
    } else {
        if (alarmTicks > 0) {
            alarmTicks--;
            Led_toggleState(LED_ONE);
        }
    }
}

int main(void) {
    LCD_init();
    Led_init(LED_ONE);

    currentTime = inputTime("Set Current Time");
    if (currentTime == NULL) {
        LCD_setLine(LINE_ONE, "MemError");
        while (true);
        return 1;
    }
    alarmTime = inputTime("Set Alarm Time");
    if (alarmTime == NULL) {
        LCD_setLine(LINE_ONE, "MemError");
        while (true);
        return 1;
    }
    
    LCD_clear();
    
    wholeSecond = true;
    Timer_init();
    Timer_setInterval(1, tick);
    
    while (true);
    
	return 0;
}
