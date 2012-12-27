#include "time_input.c"
#include "sortes.h"

interruptFunction btnOneInterrupt, btnTwoInterrupt;

void storeInterrupts() {
    if (Button_hasInterrupt(BUTTON_ONE)) {
        btnOneInterrupt = Button_getInterrupt(BUTTON_ONE);
    } else {
        btnOneInterrupt = NULL;
    }

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
    }

    if (btnTwoInterrupt) {
        Button_setInterrupt(BUTTON_Two, btnTwoInterrupt);
        btnTwoInterrupt = NULL;
    } else {
        Button_clearInterrupt(BUTTON_TWO);
    }
}

typedef enum {INPUT_HOURS, INPUT_MINUTES, INPUT_SECONDS} InputState;

InputState state;
Time time;
bool done;

void printTime() {
    char timeStr[9];
    Time_print(time, timeStr);
    LCD_setLine(LINE_TWO, timeStr);
}

void nextNumber() {
    if (state == INPUT_HOURS)
        state = INPUT_MINUTES;
    else if (state == INPUT_MINUTES)
        state = INPUT_SECONDS;
    else {
        state = NULL;
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
    
    Time retVal = time;
    time = NULL;
    return retVal;
}