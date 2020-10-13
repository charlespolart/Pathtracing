#ifndef RAND_H
#define RAND_H

#include <random>
#include <thread>

class Rand
{
public:
    static double uniform_random(double a, double b)
    {
        static thread_local std::mt19937 gen(std::hash<std::thread::id>() (std::this_thread::get_id()));
        std::uniform_real_distribution<double> dis(a, b);
        return (dis(gen));
    }
};

#endif // RAND_H
