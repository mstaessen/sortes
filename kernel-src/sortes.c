#include "sortes.h"
#include "HardwareProfile.h"
#include "LCDBlocking.h"
#include <string.h>
#include <stdlib.h>

/*
 * In the experiments, timer0 ticked 12497920 + 168 times to complete two seconds...
 * This is approx. 48820 TMR0L overflows in 2 seconds
 * Ergo: 48820 overflows / 2 seconds = 24410 overflows / second 
 *                                   = 12205 overflows / 500 ms
 */

#define OVERFLOWS_PER_HALF_SECOND 12205

unsigned int overflowCount = 0;
unsigned int timeoutCount = 0;

interruptFunction buttonOneInterruptFunction;
interruptFunction buttonTwoInterruptFunction;
interruptFunction timerInterruptFunction;

int min(int a, int b)
{
    return a > b ? b : a;
}

void interrupt(void) __interrupt(1)
{
    if (INTCONbits.T0IF) {
        overflowCount += 1;
        if (overflowCount == timeoutCount) {
            if (timerInterruptFunction) {
                timerInterruptFunction();
            }
            Timer_reset();
        }
        INTCONbits.T0IF = 0;
    }
    
    if (INTCON3bits.INT3F) {
        if (buttonOneInterruptFunction) {
            buttonOneInterruptFunction();
        }
        INTCON3bits.INT3F = 0;
    }
    
    if (INTCON3bits.INT1F) {
        if (buttonTwoInterruptFunction) {
            buttonTwoInterruptFunction();
        }
        INTCON3bits.INT1F = 0;
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

void LCD_init(void)
{
    LCDInit();
    LED3_TRIS = 0;
}

void LCD_setBacklightState(bool on)
{
    LED3_IO = on;
}

bool LCD_getBacklightState(void)
{
    return LED3_IO;
}

void LCD_toggleBacklightState(void)
{
    LED3_IO ^= 1;
}

void LCD_clear(void) 
{
    LCD_setLine(LINE_ONE, "                ");
    LCD_setLine(LINE_TWO, "                ");
}

void LCD_setLine(Line line, char *content)
{
    char *start = (char *)&LCDText;
    if (line == LINE_TWO)
        start += 16;
    
    strncpy( start, content, min((int) strlen(content), 16) );
    LCDUpdate();
}

void LCD_displayString(char *content, int offset)
{
    if (offset < 33) {
        strncpy( (char *)(&LCDText + offset), content, min(strlen(content), 32 - offset) );
        LCDUpdate();
    }
}

void Timer_init(void)
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

void Timer_setActive(bool on)
{
    T0CONbits.TMR0ON = on;
}

bool Timer_isActive(void)
{
    return T0CONbits.TMR0ON;
}

void Timer_reset(void)
{
    overflowCount = 0;
}

void Timer_setTimeout(time_t nbHalfSeconds)
{
    timeoutCount = nbHalfSeconds * OVERFLOWS_PER_HALF_SECOND;
    Timer_reset();
}

void Timer_setInterrupt(interruptFunction function)
{
    timerInterruptFunction = function;
}