#include "delay.h"

Delay::Delay()
{
}

void Delay::delayAsync(int msec, std::function<void(void)> callback)
{
    QTimer::singleShot(msec, callback);
}
