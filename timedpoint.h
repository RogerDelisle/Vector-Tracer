#ifndef TIMEDPOINT_H
#define TIMEDPOINT_H
#include <ctime>
#include <thread>
#include <ratio>
#include <chrono>
#include <QtCore>

#define WAIT_THRESHOLD 5000000

using namespace std::chrono;

typedef duration<long long, std::micro>  TimedPointDuration;
typedef unsigned long long PointInTime;

class TimedPoint
{
public:     // Important for members to be public & in this order: support for C++17's structured bindings.
    int         x;
    int         y;
    bool        mbMove;
    PointInTime t;
    static bool bDelay;

private:
    PointInTime AssignT(void);

public:
    TimedPoint();
    TimedPoint(int = 0, int = 0, bool = false);

    TimedPoint& WaitAndGet(PointInTime& since);
};

#endif // TIMEDPOINT_H
