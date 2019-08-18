#pragma once
#include "RenderInterfaceD3D11.h"

class Timer
{
public:
    Timer(const Timer& other) : StartTime(other.StartTime), EndTime(other.EndTime) {}
    Timer(Timer&& other) noexcept : StartTime(other.StartTime), EndTime(other.EndTime) {}
    Timer& operator=(const Timer& other)
    {
        if (this == &other)
        {
            return *this;
        }
        StartTime = other.StartTime;
        EndTime = other.EndTime;
        return *this;
    }
    Timer& operator=(Timer&& other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }
        StartTime = other.StartTime;
        EndTime = other.EndTime;
        return *this;
    }
    Timer(bool StartNow)
    {
        if(StartNow)
        {
            Start();
        }
    };
    Timer()
    {
        
    }
    ~Timer() = default;

    void Start();
    void Reset();
    long long ElapsedHours();
    long long ElapsedMinutes();
    long long ElapsedSeconds();
    long long ElapsedMilliseconds();
    long long ElapsedMicroseconds();
    long long ElapsedNanoseconds();

private:
    std::chrono::steady_clock::time_point StartTime;
    std::chrono::steady_clock::time_point EndTime;
};

