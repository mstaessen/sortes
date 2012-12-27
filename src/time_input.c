#include <stdlib.h>
#include "time_input.h"
#include "time.h"
#include "sortes.h"

interruptFunction btnOneInterrupt, btnTwoInterrupt;

void storeInterrupts() {
    Button_setActive(BUTTON_ONE, true);
    if (Button_hasInterrupt(BUTTON_ONE)) {
        btnOneInterrupt = Button_getInterrupt(BUTTON_ONE);
    } else {
        btnOneInterrupt = NULL;
    }

    Button_setActive(BUTTON_TWO, true);
    if (Button_hasInterrupt(BUTTON_TWO)) {
        btnOneInterrupt = Button_getInterrupt(BUTTON_TWO);
    } else {
        btnOneInterrupt = NULL;
    }
}

void restoreInterrupts() {
    if (btnOneInterrupt) {
        Button_setInterrupt(BUTTON_ONE, btnOneInterrupt);
        btnOneInterrupt = NULL;
    } else {
        Button_clearInterrupt(BUTTON_ONE);
        Button_setActive(BUTTON_ONE, false);
    }

    if (btnTwoInterrupt) {
        Button_setInterrupt(BUTTON_TWO, btnTwoInterrupt);
        btnTwoInterrupt = NULL;
    } else {
        Button_clearInterrupt(BUTTON_TWO);
        Button_setActive(BUTTON_TWO, false);
    }
}

typedef enum {INPUT_HOURS, INPUT_MINUTES, INPUT_SECONDS} InputState;

static InputState state;
static Time time;
static bool done;

void printTime() {
    outputTime(time);
}

void nextNumber() {
    if (state == INPUT_HOURS)
        state = INPUT_MINUTES;
    else if (state == INPUT_MINUTES)
        state = INPUT_SECONDS;
    else {
        done = true;
    }
}

void addOne() {
    if (state == INPUT_HOURS) {
        Time_addHour(time);
    } else if (state == INPUT_MINUTES) {
        Time_addMinute(time);
    } else if (state == INPUT_SECONDS) {
        Time_addSecond(time);
    } else return;
    
    printTime();
}

void setInterrupts() {
    Button_setInterrupt(BUTTON_ONE, &addOne);
    Button_setInterrupt(BUTTON_TWO, &nextNumber);
}

Time inputTime(char *text) {
    time = createTime();
    done = false;
    state = INPUT_HOURS;
    
    if (!time)
        return NULL;
    
    // show the inputline
    LCD_setLine(LINE_ONE, text);
    // print the time
    printTime();
    
    // set interrupts
    storeInterrupts();
    setInterrupts();
    
    while (!done);
    
    // reset the interrupts
    restoreInterrupts();
    
    return time;
}

void outputTime(Time t)
    char timeStr[9];
    Time_print(t, timeStr);
    LCD_setLine(LINE_TWO, timeStr);
}