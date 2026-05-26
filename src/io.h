#ifndef IO_H
#define IO_H

#include "student.h"
#include <string>


template<typename Container>
void FailoSkaitymas(const std::string& failas,
                    Container& grupe);


template<typename Container>
void IsvestiIFaila(const std::string& failas,
                   const Container& grupe);

#include "io.tpp"

#endif