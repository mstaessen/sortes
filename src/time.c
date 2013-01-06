#include "time.h"

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

struct TimeStruct {
    uint hours, minutes, seconds;
};

void initTime(Time time) {
    time->hours = time->minutes = time->seconds = 0;
}

Time createTime() {
    Time t = (Time)malloc(sizeof (struct TimeStruct));
    if (t) initTime(t);
    return t;
}

void Time_setSeconds(Time time, uint s) {
    time->seconds = s % 60;
}

uint Time_getSeconds(Time time) {
    return time->seconds;
}

void Time_setMinutes(Time time, uint m) {
    time->minutes = m % 60;
}

uint Time_getMinutes(Time time) {
    return time->minutes;
}

void Time_setHours(Time time, uint h) {
    time->hours = h % 24;
}

uint Time_getHours(Time time) {
    return time->hours;
}
    
void Time_print(Time time, char *str) {
    sprintf(str, "%02u:%02u:%02u", time->hours, time->minutes, time->seconds);
}

void Time_addSecond(Time time) {
    time->seconds = time->seconds + 1;
    if (time->seconds == 60) time->seconds = 0;
}

void Time_addMinute(Time time) {
    time->minutes = time->minutes + 1;
    if (time->minutes == 60) time->minutes = 0;
}

void Time_addHour(Time time) {
    time->hours = (time->hours + 1);
    if (time->hours == 24) time->hours = 0;
}

void Time_tick(Time time) {
    Time_addSecond(time);
    if (time->seconds == 0) {
        Time_addMinute(time);
        if (time->minutes == 0) {
            Time_addHour(time);
        }
    }
}

bool Time_equals(Time a, Time b) {
    if (a == b)
        return true;
    return (a->hours == b->hours)
        && (a->minutes == b->minutes)
            && (a->seconds == b->seconds);
}