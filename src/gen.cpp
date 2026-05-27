#include "gen.h"

#include <fstream>
#include <iomanip>
#include <random>
#include <stdexcept>



void GeneruotiFaila(
    const std::string& pav,
    int kiekis
)
{
    std::ofstream out(pav);

    if (!out)
        throw std::runtime_error(
            "Nepavyko sukurti failo"
        );

    std::mt19937 gen(std::random_device{}());

    std::uniform_int_distribution<int>
        dist(1, 10);

    int ndKiekis = 15;


    // ================= HEADER =================

    out << std::left
        << std::setw(20)
        << "Vardas"

        << std::setw(20)
        << "Pavarde";

    for (int i = 1; i <= ndKiekis; i++)
    {
        out << std::setw(6)
            << ("ND" + std::to_string(i));
    }

    out << std::setw(6)
        << "Egz."
        << '\n';


    // ================= STUDENTAI =================

    for (int i = 1; i <= kiekis; i++)
    {
        out << std::left

            << std::setw(20)
            << ("Vardas" + std::to_string(i))

            << std::setw(20)
            << ("Pavarde" + std::to_string(i));


        for (int j = 0; j < ndKiekis; j++)
        {
            out << std::setw(6)
                << dist(gen);
        }

        out << std::setw(6)
            << dist(gen)
            << '\n';
    }
}