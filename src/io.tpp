#pragma once

#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>


template<typename Container>
void FailoSkaitymas(const std::string& failas,
                    Container& grupe)
{
    std::ifstream fin(failas);

    if (!fin)
        throw std::runtime_error("Nepavyko atidaryti failo");

    grupe.clear();

    std::string line;

    getline(fin, line);

    std::istringstream hs(line);

    std::string tok;
    int nd_kiek = 0;

    while (hs >> tok)
    {
        if (tok.rfind("ND", 0) == 0)
            nd_kiek++;
    }

    Student A;
while (fin >> A.vardas >> A.pavarde)
    {
        A.paz.clear();

        for (int i = 0; i < nd_kiek; i++)
        {
            int x;
            fin >> x;
            A.paz.push_back(x);
        }

        fin >> A.egz;

        SkaiciuotiGalutinius(A);

        grupe.push_back(A);
    }
}



template<typename Container>
void IsvestiIFaila(const std::string& failas,
                   const Container& grupe)
{
    std::ofstream out(failas);

    if (!out)
        throw std::runtime_error("Nepavyko sukurti failo");

    out << std::left
        << std::setw(20) << "Vardas"
        << std::setw(20) << "Pavarde"
        << std::setw(15) << "Galutinis"<< '\n';

    out << std::string(55, '-') << '\n';

    for (const auto& s : grupe)
    {
        out << std::setw(20) << s.vardas
            << std::setw(20) << s.pavarde
            << std::fixed
            << std::setprecision(2)
            << s.rez_vid
            << '\n';
    }
}