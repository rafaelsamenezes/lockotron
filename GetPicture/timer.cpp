#include "timer.h"

Timer::Timer()
{

}

void Timer::waitTime(clock_t ms){
    clock_t expectedTime = (ms + clock());

    while (expectedTime > clock());
}
