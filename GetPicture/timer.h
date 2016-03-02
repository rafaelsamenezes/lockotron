#ifndef TIMER_H
#define TIMER_H

#include <time.h>

class Timer
{
public:
    Timer();
    void waitTime(clock_t ms);
};

#endif // TIMER_H
