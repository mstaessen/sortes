#ifndef __SORTES_H__
#define __SORTES_H__

#include "bool.h"

typedef void (*interruptFunction)();

typedef unsigned int time_t;

// Buttons

typedef enum { BUTTON_ONE, BUTTON_TWO } Button;

void Button_setActive(Button button, bool active);

void Button_setInterrupt(Button button, interruptFunction func);
bool Button_hasInterrupt(Button button);
interruptFunction Button_getInterrupt(Button button);
void Button_clearInterrupt(Button button);

// LEDs

typedef enum { LED_ONE, LED_TWO, LED_THREE } Led;

void Led_setState(Led led, bool on);

// LCD

typedef enum { LINE_ONE, LINE_TWO } Line;

void LCD_init();

void LCD_setLine(Line line, char *content);

// Timer

void Timer_setInterval(time_t timeout, time_t interval, interruptFunction func);

void Timer_setTimeout(time_t time, interruptFunction func);

#endif