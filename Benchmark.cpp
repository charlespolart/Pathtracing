#include "Benchmark.h"

Benchmark::Benchmark()
{
}

Benchmark::~Benchmark()
{
}

void Benchmark::start()
{
    this->startPoint = std::chrono::steady_clock::now();
}

benchTime_t Benchmark::getBenchTime()
{
    long long ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()-this->startPoint).count();
    benchTime_t benchTime;

    if (ms >= 3600000)
    {
        benchTime.hours = ms/3600000;
        benchTime.hours_str = std::to_string(benchTime.hours)+"h";
        benchTime.fullTime_str += benchTime.hours_str+" ";
        ms %= 3600000;
    }
    if (ms >= 60000)
    {
        benchTime.minutes = ms/60000;
        benchTime.minutes_str = std::to_string(benchTime.minutes)+"m";
        benchTime.fullTime_str += benchTime.minutes_str+" ";
        ms %= 60000;
    }
    if (ms >= 1000)
    {
        benchTime.secondes = ms/1000;
        benchTime.secondes_str = std::to_string(benchTime.secondes)+"s";
        benchTime.fullTime_str += benchTime.secondes_str+" ";
        ms %= 1000;
    }
    benchTime.mSecondes = ms;
    benchTime.mSecondes_str = std::to_string(benchTime.mSecondes)+"ms";
    benchTime.fullTime_str += benchTime.mSecondes_str;
    return (benchTime);
}
