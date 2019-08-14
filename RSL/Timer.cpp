#include "Timer.h"

void Timer::Start()
{
    StartTime = std::chrono::steady_clock::now();
}

void Timer::Reset()
{
    StartTime = std::chrono::steady_clock::now();
}

long long Timer::ElapsedHours()
{
    EndTime = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::hours>(EndTime - StartTime).count();
}

long long Timer::ElapsedMinutes()
{
    EndTime = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::minutes>(EndTime - StartTime).count();
}

long long Timer::ElapsedSeconds()
{
    EndTime = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::seconds>(EndTime - StartTime).count();
}

long long Timer::ElapsedMilliseconds()
{
    EndTime = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(EndTime - StartTime).count();
}

long long Timer::ElapsedMicroseconds()
{
    EndTime = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(EndTime - StartTime).count();
}

long long Timer::ElapsedNanoseconds()
{
    EndTime = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(EndTime - StartTime).count();
}