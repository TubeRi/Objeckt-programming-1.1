#include "utils.h"

#include <iostream>
#include <limits>
#include <cctype>
#include <stdexcept>

int RandomPazymys(std::mt19937& gen)
{
    static std::uniform_int_distribution<int> dist(1, 10);
    return dist(gen);
}

std::string RandomIsSaraso(const std::vector<std::string>& sar, std::mt19937& gen)
{
    if (sar.empty())
    {
        throw std::runtime_error("Klaida: tuscias sarasas atsitiktiniam parinkimui.");
    }

    std::uniform_int_distribution<int> dist(0, static_cast<int>(sar.size()) - 1);
    return sar[dist(gen)];
}

std::string SkaitytiZodi(const std::string& zinute)
{
    std::string s;

    while (true)
    {
        std::cout << zinute;
        std::cin >> s;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Klaida: nepavyko nuskaityti zodzio.\n";
            continue;
        }

        bool geras = !s.empty();

        for (char c : s)
        {
            unsigned char uc = static_cast<unsigned char>(c);
            if (!std::isalpha(uc))
            {
                geras = false;
                break;
            }
        }

        if (geras)
        {
            return s;
        }

        std::cout << "Klaida: galima ivesti tik raides.\n";
    }
}

char SkaitytiChar(const std::string& zinute, const std::string& galimi)
{
    char c;

    while (true)
    {
        std::cout << zinute;
        std::cin >> c;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Klaida: nepavyko nuskaityti simbolio.\n";
            continue;
        }

        if (galimi.find(c) != std::string::npos)
        {
            return c;
        }

        std::cout << "Klaida: netinkamas pasirinkimas.\n";
    }
}

int SkaitytiInt(const std::string& zinute)
{
    int x;

    while (true)
    {
        std::cout << zinute;
        std::cin >> x;

        if (!std::cin.fail())
        {
            return x;
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Klaida: reikia ivesti sveika skaiciu.\n";
    }
}

double SkaitytiDouble(const std::string& zinute)
{
    double x;

    while (true)
    {
        std::cout << zinute;
        std::cin >> x;

        if (!std::cin.fail())
        {
            return x;
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Klaida: reikia ivesti realuji skaiciu.\n";
    }
}

int SkaitytiPazymi(const std::string& zinute, bool leistiNuli)
{
    while (true)
    {
        int x = SkaitytiInt(zinute);

        if (leistiNuli && x == 0)
        {
            return 0;
        }

        if (x >= 1 && x <= 10)
        {
            return x;
        }

        if (leistiNuli)
        {
            std::cout << "Klaida: galima ivesti skaiciu nuo 1 iki 10 arba 0 baigimui.\n";
        }
        else
        {
            std::cout << "Klaida: galima ivesti tik skaiciu nuo 1 iki 10.\n";
        }
    }
}