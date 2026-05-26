#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <filesystem>

#include "student.h"
#include "gen.h"
#include "io.h"
#include "split.h"
#include "utils.h"

using std::cout;
using std::endl;



template<typename Container>
void TestuotiKonteineri(
    const std::string& failas,
    const std::string& pavadinimas
)
{
    Container studentai;
    Container vargsiukai;
    Container kietiakai;

    cout << "\n========== "
         << pavadinimas<< " ==========\n";


    double skaitymas = Laikas([&]()
    {
        FailoSkaitymas(failas, studentai);
    });

    cout << "Skaitymas: "
         << skaitymas
         << " s\n";


    double skirstymas = Laikas([&]()
    {
        Strategija1(studentai,
                    vargsiukai,
                    kietiakai);
    });

    cout << "Skirstymas: "
         << skirstymas
         << " s\n";


    double isvedimas = Laikas([&]()
    {
        IsvestiIFaila(
            "vargsiukai_" + pavadinimas + ".txt",
            vargsiukai
        );

        IsvestiIFaila(
            "kietiakai_" + pavadinimas + ".txt",
            kietiakai);
    });

    cout << "Isvedimas: "
         << isvedimas
         << " s\n";
}


int main()
{
    std::filesystem::create_directory("data");

    try
    {
        GeneruotiFaila("data/sugeneruota1000.txt", 1000);
        GeneruotiFaila("data/sugeneruota10000.txt", 10000);
        GeneruotiFaila("data/sugeneruota100000.txt", 100000);
        GeneruotiFaila("data/sugeneruota1000000.txt", 1000000);


        std::string failas = "data/sugeneruota100000.txt";


        TestuotiKonteineri<std::vector<Student>>(
            failas,
            "vector"
        );


        TestuotiKonteineri<std::list<Student>>(
            failas,
            "list"
        );


        TestuotiKonteineri<std::deque<Student>>(
            failas,
            "deque"
        );
    }
    catch (const std::exception& e)
    {
        cout << e.what() << endl;
    }

    return 0;
}