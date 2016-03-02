#include "Timer.h"

//=======================================================================
Timer::Timer ( )
    :isRunning(false), myStartingTime(0)
{
}

//=======================================================================
Timer::~Timer ( )
{
}

//=======================================================================
bool Timer::start ( )
{
    if ( !isRunning )
    {
        isRunning = true;
        myStartingTime = GetTickCount64( );
    }
    return isRunning;
}

//=======================================================================
unsigned long long Timer::stop ( )
{
    if ( isRunning )
    {
        return GetTickCount64( ) - myStartingTime;
        isRunning = false;
    }
    return 0;
}

//=======================================================================
unsigned long long Timer::restart ( )
{
    if ( isRunning )
    {
        unsigned long long delta = GetTickCount64( ) - myStartingTime;
        myStartingTime = GetTickCount64 ( );
        return delta;
    }
    return 0;
}

//=======================================================================
unsigned long long Timer::elapsedTime ( )
{
    if ( isRunning )
    {
        return GetTickCount64 ( ) - myStartingTime;
    }
    return 0;
}