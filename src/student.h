
#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>

struct Student
{
    std::string vardas;
    std::string pavarde;

    std::vector<int> paz;

    int egz = 0;

    double rez_vid = 0.0;
    double rez_med = 0.0;
};

double Vidurkis(const std::vector<int>& paz);
double Mediana(std::vector<int> paz);
void SkaiciuotiGalutinius(Student& A);

#endif