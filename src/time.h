#ifndef __TIME_H_
#define __TIME_H_

typedef unsigned int uint;

struct TimeStruct;
typedef struct TimeStruct *Time;

void initTime(Time);
Time createTime();
void deleteTime(Time);

void Time_setSeconds(Time, uint);
uint Time_getSeconds(Time);

void Time_setMinutes(Time, uint);
uint Time_getMinutes(Time);

void Time_setHours(Time, uint);
uint Time_getHours(Time);

void Time_print(Time, char *);

void Time_addSecond(Time);
void Time_addMinute(Time);
void Time_addHour(Time);

void Time_tick(Time);

bool Time_equals(Time, Time);

#endif