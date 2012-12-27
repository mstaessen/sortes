#include "sortes.h"
#include "HardwareProfile.h"
#include "LCDBlocking.h"
#include <string.h>
#include <stdlib.h>

interruptFunction buttonOneInterruptFunction;
interruptFunction buttonTwoInterruptFunction;
interruptFunction timerInterruptFunction;

int min(int a, int b)
{
    return a > b ? b : a;
}

void interrupt(void) __interrupt (1)
{
    if (BUTTON0_IO && buttonOneInterruptFunction) {
        buttonOneInterruptFunction();
        BUTTON0_IO = 0;
    }
    
    if (BUTTON1_IO && buttonTwoInterruptFunction) {
        buttonTwoInterruptFunction();
        BUTTON1_IO = 0;
    }
    
    if (INTCONbits.T0IF && timerInterruptFunction) {
        timerInterruptFunction();
        INTCONbits.T0IF = 0;
    }
}

void Button_setActive(Button button, bool active)
{
    switch (button) {
        case BUTTON_ONE:
            BUTTON0_TRIS = active;
            break;
        case BUTTON_TWO:
            BUTTON1_TRIS = active;
            break;
    }
}

bool Button_isActive(Button button)
{
    switch (button) {
        case BUTTON_ONE:
            return BUTTON0_TRIS;
            break;
        case BUTTON_TWO:
            return BUTTON1_TRIS;
            break;
    }
    return false;
}

void Button_setInterrupt(Button button, interruptFunction func)
{
    switch (button) {
        case BUTTON_ONE:
            buttonOneInterruptFunction = func;
            break;
        case BUTTON_TWO:
            buttonTwoInterruptFunction = func;
            break;
    }
}

bool Button_hasInterrupt(Button button)
{
    switch (button) {
        case BUTTON_ONE:
            return buttonOneInterruptFunction != NULL;
            break;
        case BUTTON_TWO:
            return buttonTwoInterruptFunction != NULL;
            break;
    }
    return false;
}

interruptFunction Button_getInterrupt(Button button)
{
    switch (button) {
        case BUTTON_ONE:
            return buttonOneInterruptFunction;
            break;
        case BUTTON_TWO:
            return buttonTwoInterruptFunction;
            break;
    }
    return NULL;
}

void Button_clearInterrupt(Button button)
{
    switch (button) {
        case BUTTON_ONE:
            buttonOneInterruptFunction = NULL;
            break;
        case BUTTON_TWO:
            buttonTwoInterruptFunction = NULL;
            break;
    }
}

void Led_init(Led led)
{
    switch (led) {
        case LED_ONE:
            LED0_TRIS = 0;
            break;
        case LED_TWO:
            LED1_TRIS = 0;
            break;
        case LED_THREE:
            LED2_TRIS = 0;
            break;
    }
}

void Led_setState(Led led, bool on)
{
    switch (led) {
        case LED_ONE:
            LED0_IO = on;
            break;
        case LED_TWO:
            LED1_IO = on;
            break;
        case LED_THREE:
            LED2_IO = on;
            break;
    }
}

bool Led_getState(Led led)
{
    switch (led) {
        case LED_ONE:
            return LED0_IO;
            break;
        case LED_TWO:
            return LED1_IO
            break;
        case LED_THREE:
            return LED2_IO;
            break;
    }
    return false;
}

void LCD_init()
{
    LCDInit();
}

void LCD_setBacklightState(bool on)
{
    PORTGbits.RG5 = on;
}

void LCD_setLine(Line line, char *content)
{
    strncpy((char *)&LCDText, content, min((int) strlen(content), 16));
    // Clear the rest of the line...
    for(size_t i = strlen(content) + 1; i < 16; i++) {
        strncpy((char *)&LCDText + i, " ", 1);
    }
    LCDUpdate();
}

void Timer_setInterval(time_t timeout, time_t interval, interruptFunction func)
{
    T0CONbits.T08BIT = 1;
    T0CONbits.T0CS = 0;
    T0CONbits.PSA = 1;
    T0CONbits.TMR0ON = 1;
    INTCONbits.T0IE = 1;
    INTCON2bits.T0IP = 1;
    INTCONbits.T0IF = 0;
    
    // TODO configure timer for interrupt
    timerInterruptFunction = func;
}

void Timer_setTimeout(time_t time, interruptFunction func)
{
    
}

