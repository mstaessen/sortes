#include "sortes.h"
#include "HardwareProfile.h"
#include "LCDBlocking.h"
#include <string.h>
#include <stdlib.h>

#define NB_INTERRUPTS_PER_HALF_SECOND 12206
#define REMAINDER_TICKS_PER_HALF_SECOND 22 

unsigned int count = 0;

interruptFunction buttonOneInterruptFunction;
interruptFunction buttonTwoInterruptFunction;
interruptFunction timerInterruptFunction;

int min(int a, int b)
{
    return a > b ? b : a;
}

void preloadTimer() 
{
    TMR0L = REMAINDER_TICKS_PER_HALF_SECOND;
    count = 0;
}

void resetTimer() 
{
    TMR0L += REMAINDER_TICKS_PER_HALF_SECOND;
    count = 0;
}

void interrupt(void) __interrupt(1)
{
    if (INTCONbits.T0IF) {
        if (count++ == NB_INTERRUPTS_PER_HALF_SECOND) {
            if (timerInterruptFunction) timerInterruptFunction();
            resetTimer();
        }
        INTCONbits.T0IF = 0;
    }
    
    if (INTCON3bits.INT3F) {
        INTCON3bits.INT3F = 0;
        if (buttonOneInterruptFunction)
            buttonOneInterruptFunction();
    }
    
    if (INTCON3bits.INT1F) {
        INTCON3bits.INT1F = 0;
        if (buttonTwoInterruptFunction)
            buttonTwoInterruptFunction();
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
    
    INTCONbits.GIE = 1;
    INTCON3bits.INT1P = 1;
    INTCON3bits.INT1IE = 1;
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
            return LED1_IO;
            break;
        case LED_THREE:
            return LED2_IO;
            break;
    }
    return false;
}

void Led_toggleState(Led led)
{
    switch (led) {
        case LED_ONE:
            LED0_IO ^= 1;
            break;
        case LED_TWO:
            LED1_IO ^= 1;
            break;
        case LED_THREE:
            LED2_IO ^= 1;
            break;
    }
}

void LCD_init()
{
    LCDInit();
    LED3_TRIS = 0;
}

void LCD_setBacklightState(bool on)
{
    LED3_IO = on;
}

bool LCD_getBacklightState()
{
    return LED3_IO;
}

void LCD_toggleBacklightState()
{
    LED3_IO ^= 1;
}

void LCD_clear() {
    LCD_setLine(LINE_ONE, "");
    LCD_setLine(LINE_TWO, "");
}

void LCD_setLine(Line line, char *content)
{
    char *start = (char *)&LCDText;
    if (line == LINE_TWO)
        start += 16;
    
    strncpy( start, content, min((int) strlen(content), 16) );
    LCDUpdate();
}

void Timer_init()
{
    // Use 8-bit operation
    T0CONbits.T08BIT = 1;
    // Use internal instruction cycle clock
    T0CONbits.T0CS = 0;
    // Don't use the prescaler
    T0CONbits.PSA = 1;
    // Enable interrupts
    INTCONbits.TMR0IE = 1;
}

void Timer_setInterval(time_t interval, interruptFunction func)
{
    preloadTimer();
    timerInterruptFunction = func;
}