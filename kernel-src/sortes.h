#ifndef __SORTES_H__
#define __SORTES_H__

#define __SDCC__
#define __18F97J60

#include "bool.h"

typedef void (*interruptFunction)();

typedef unsigned int time_t;

// Buttons

typedef enum { BUTTON_ONE, BUTTON_TWO } Button;

void Button_setActive(Button button, bool active);

bool Button_isActive(Button button);

void Button_setInterrupt(Button button, interruptFunction func);

bool Button_hasInterrupt(Button button);

interruptFunction Button_getInterrupt(Button button);

void Button_clearInterrupt(Button button);

// LEDs

typedef enum { LED_ONE, LED_TWO, LED_THREE } Led;

void Led_init(Led led);

void Led_setState(Led led, bool on);

bool Led_getState(Led led);

void Led_toggleState(Led led);

// LCD

typedef enum { LINE_ONE, LINE_TWO } Line;

void LCD_init(void);

void LCD_setBacklightState(bool on);

bool LCD_getBacklightState(void);

void LCD_toggleBacklightState(void);

void LCD_setLine(Line line, char *content);

void LCD_displayString(char *content, int offset);

void LCD_clear(void);

// Timer

void Timer_init(void);

void Timer_setActive(bool on);

bool Timer_isActive(void);

void Timer_reset(void);

void Timer_setTimeout(time_t nbHalfSeconds);

void Timer_setInterrupt(interruptFunction function);

#endif
