#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <random>
#include <chrono>

int RandomPazymys(std::mt19937& gen);
std::string RandomIsSaraso(const std::vector<std::string>& sar, std::mt19937& gen);

std::string SkaitytiZodi(const std::string& zinute);
char SkaitytiChar(const std::string& zinute, const std::string& galimi);
int SkaitytiInt(const std::string& zinute);
double SkaitytiDouble(const std::string& zinute);
int SkaitytiPazymi(const std::string& zinute, bool leistiNuli = false);

template <typename Func>
double Laikas(Func&& f)
{
    using clock = std::chrono::high_resolution_clock;
    auto start = clock::now();
    f();
    auto end = clock::now();
    std::chrono::duration<double> diff = end - start;
    return diff.count();
}

#endif