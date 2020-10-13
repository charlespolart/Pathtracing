#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <chrono>
#include <string>
#include <iostream>

struct benchTime_t
{
    int hours = 0;
    int minutes = 0;
    int secondes = 0;
    int mSecondes = 0;
    std::string hours_str;
    std::string minutes_str;
    std::string secondes_str;
    std::string mSecondes_str;
    std::string fullTime_str;
};

class Benchmark
{
public:
    Benchmark();
    ~Benchmark();

public:
    void start();
    void pause();
    void resume();
    benchTime_t getBenchTime();

private:
    std::chrono::steady_clock::time_point _startPoint;
    std::chrono::steady_clock::time_point _pausePoint;
};

#endif // BENCHMARK_H
