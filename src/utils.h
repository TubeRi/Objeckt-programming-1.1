#ifndef UTILS_H
#define UTILS_H

#include <chrono>

#include <string>
#include <vector>
#include <random>

template<typename Func>
double Laikas(Func f)
{
    auto start = std::chrono::high_resolution_clock::now();

    f();

    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration<double>(end - start).count();
}

#endif