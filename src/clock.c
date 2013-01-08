#define __SDCC__
#define __CX18

#include <bool.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <sortes.h>
#include "time.h"

#define ALARM_DURATION_IN_HALF_SECONDS 60 

unsigned char _MALLOC_SPEC heap[256];

Time _time, _alarm;
unsigned short _alarmTicks = 0;
bool _wholeSecond = true;
bool _alarmSetup = 0;
enum { 
    OFFSET_HOURS = 22, 
    OFFSET_MINUTES = 25, 
    OFFSET_SECONDS = 28, 
    OFFSET_SET_TIME = 6, 
    OFFSET_SET_ALARM = 5, 
    OFFSET_ALARM = 7, 
    OFFSET_PLUS = 0, 
    OFFSET_OK = 16 
} _displayOffset = OFFSET_HOURS;

void displayTime(Time time)
{
    char str[9];
    Time_print(time, str);
    LCD_displayString(str, OFFSET_HOURS);
}

void ringAlarm(void) {
    _alarmTicks = ALARM_DURATION_IN_HALF_SECONDS;
    LCD_displayString("Alarm!", OFFSET_ALARM);
}

void tick(void)
{
    if (_wholeSecond) {
        Time_tick(_time);
        displayTime(_time);
    
        if (Time_equals(_time, _alarm)) {
            ringAlarm();
        }
        _wholeSecond = false;
    } else {
        _wholeSecond = true;
    }
    
    if (_alarmTicks > 0) {
        Led_toggleState(LED_ONE);
        _alarmTicks -= 1;
        
        if (_alarmTicks == 0) {
            LCD_displayString("      ", OFFSET_ALARM);
        }
    }
}

void setupTick(void)
{
    if (_wholeSecond) {
        if (!_alarmSetup) {
            displayTime(_time);
        } else {
            displayTime(_alarm);
        }
        _wholeSecond = false;
    } else {
        // (user feedback) make the digits disappear for half a second
        LCD_displayString("  ", _displayOffset);
        _wholeSecond = true;
    }
}

void increaseCurrentUnit(Time time)
{
    switch (_displayOffset) {
        case OFFSET_HOURS:
            Time_addHour(time);
            break;
        case OFFSET_MINUTES:
            Time_addMinute(time);
            break;
        case OFFSET_SECONDS:
            Time_addSecond(time);
            break;
    }
}

void increase(void)
{
    if (_alarmSetup) {
        increaseCurrentUnit(_alarm);
    } else {
        increaseCurrentUnit(_time);
    }
}

void proceed(void)
{
    switch (_displayOffset) {
        case OFFSET_HOURS:
            _displayOffset = OFFSET_MINUTES;
            break;
        case OFFSET_MINUTES:
            _displayOffset = OFFSET_SECONDS;
            break;
        case OFFSET_SECONDS:
            _displayOffset = OFFSET_HOURS;

            if (_alarmSetup) {
                LCD_clear();
                Timer_setInterrupt(tick);
                Button_clearInterrupt(BUTTON_ONE);
                Button_clearInterrupt(BUTTON_TWO);
            } else {
                _alarmSetup = true;
                LCD_displayString("Set  Alarm", OFFSET_SET_ALARM);
            }
            break;
    }
}

void main(void) 
{
    _time = createTime();
    _alarm = createTime();
    
    Led_init(LED_ONE);
    Led_setState(LED_ONE, false);
    
    LCD_init();
    LCD_displayString("+", OFFSET_PLUS);
    LCD_displayString("Set Time", OFFSET_SET_TIME);
    LCD_displayString("OK", OFFSET_OK);
    
    Button_setActive(BUTTON_ONE, true);
    Button_setInterrupt(BUTTON_ONE, proceed);
    
    Button_setActive(BUTTON_TWO, true);
    Button_setInterrupt(BUTTON_TWO, increase);

    Timer_init();
    Timer_setTimeout(1);
    Timer_setInterrupt(setupTick);
    Timer_setActive(true);
    
    while(true);
}