#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

volatile int timerCount;
volatile int timerSeconds;

void Sleep(int seconds);
void PIC_TimerSetup();
void TimerCountUp();
void ResetTimerCount();
int TimerGetCount();
int TimerGetSeconds();
void TimerSecondUp();

#endif