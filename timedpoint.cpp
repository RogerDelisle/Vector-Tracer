#include "timedpoint.h"
#include <iostream>

bool TimedPoint::bDelay = false;

PointInTime TimedPoint::AssignT(void)
{
    unsigned long long tt = system_clock::now().time_since_epoch().count();
    // System clock actually returns epoch time in 1/10ths of microseconds. Correct before storing.
    lldiv_t res = lldiv(tt, 10);
    return (PointInTime)res.quot;
}

TimedPoint::TimedPoint() : x(0), y(0)
{
    t = AssignT();
}

TimedPoint::TimedPoint(int ix, int iy, bool ibMove) : x(ix), y(iy), mbMove(ibMove)
{
    t = AssignT();
    TimedPoint::bDelay = false;
}

//No longer used for Qt animation. Keep method for later use in modulating signal.
TimedPoint& TimedPoint::WaitAndGet(PointInTime& since)
{
    if (bDelay && (since > 0)) {
        PointInTime pit_diff = t - since;

        if (pit_diff > 0) {
            pit_diff = pit_diff > WAIT_THRESHOLD ? WAIT_THRESHOLD : pit_diff;
            TimedPointDuration diff = microseconds(pit_diff);
            std::this_thread::sleep_for(diff);
        }
    }
    since = t;
    return *this;
}
