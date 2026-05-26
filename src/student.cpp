#include "student.h"
#include <algorithm>


double Vidurkis(const std::vector<int>& paz)
{
    if (paz.empty()) return 0.0;

    int suma = 0;

    for (int x : paz)
        suma += x;

    return static_cast<double>(suma) / paz.size();
}


double Mediana(std::vector<int> paz)
{
    if (paz.empty()) return 0.0;

    std::sort(paz.begin(), paz.end());

    int n = paz.size();

    if (n % 2 == 0)
        return (paz[n / 2 - 1] + paz[n / 2]) / 2.0;

    return paz[n / 2];
}


void SkaiciuotiGalutinius(Student& A)
{
    double vid = Vidurkis(A.paz);
    double med = Mediana(A.paz);

    A.rez_vid = 0.4 * vid + 0.6 * A.egz;
    A.rez_med = 0.4 * med + 0.6 * A.egz;
}