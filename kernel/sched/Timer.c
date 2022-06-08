#include "Timer.h"
void PIC_TimerSetup()
{
    timerCount = 0;
    timerSeconds = 0;
}

void TimerCountUp()
{
    timerCount++;
}

void ResetTimerCount()
{
    timerCount = 0;
}

int TimerGetCount()
{
    return timerCount;
}

int TimerGetSeconds()
{
    return timerSeconds;
}
//.
void TimerSecondUp()
{
    timerSeconds++;
}

void Sleep(int seconds)
{
    uint64_t secondsEnd = TimerGetSeconds() + seconds;
    while(TimerGetSeconds() < secondsEnd)
    {
        __asm__ ("nop");
    }
}