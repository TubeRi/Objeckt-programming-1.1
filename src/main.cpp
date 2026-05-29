#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <filesystem>
#include <sstream>
#include "Vector.h"
#include <chrono>

#include "student.h"
#include "gen.h"
#include "io.h"
#include "split.h"
#include "utils.h"

using std::cout;
using std::endl;

void Testai()
{
    Student a(
        "Jonas",
        "Jonaitis",
        {10, 9, 8},
        9);

 
    Student b(a);

    
    Student c;
    c = a;

    Student d(std::move(a));

    
    Student e;
    e = std::move(b);

    
    Student s;

    std::stringstream ss;

    ss << "Petras Petraitis";

    ss >> s;

    std::cout << s << std::endl;

    Vector<int> test;

    test.push_back(1);

    test.push_back(2);

    test.push_back(3);

    if (test.size() == 3)
    {
        std::cout << "Vector testas OK\n";
    }
}
template <typename Container>
void TestuotiKonteineri(
    const std::string &failas,
    const std::string &pavadinimas)
{
    Container studentai;
    Container vargsiukai;
    Container kietiakai;

    cout << "\n========== "
         << pavadinimas
         << " ==========\n";

    //  SKAITYMAS 

    double skaitymas = Laikas([&]()
                              { FailoSkaitymas(failas, studentai); });

    cout << "Skaitymas: "
         << skaitymas
         << " s\n";

    //  STRATEGIJA 1 

    double strategija1 = Laikas([&]()
                                { Strategija1(
                                      studentai,
                                      vargsiukai,
                                      kietiakai); });

    cout << "Strategija 1: "
         << strategija1
         << " s\n";

    //  STRATEGIJA 2 

    Container studentai2 = studentai;

    double strategija2 = Laikas([&]()
                                { Strategija2(
                                      studentai2,
                                      vargsiukai); });

    cout << "Strategija 2: "
         << strategija2
         << " s\n";

    //  STRATEGIJA 3 

    Container studentai3 = studentai;

    double strategija3 = Laikas([&]()
                                { Strategija3(
                                      studentai3,
                                      vargsiukai); });

    cout << "Strategija 3: "
         << strategija3
         << " s\n";

    //  IŠVEDIMAS 

    double isvedimas = Laikas([&]()
                              {
        IsvestiIFaila(
            "vargsiukai_" + pavadinimas + ".txt",
            vargsiukai
        );

        IsvestiIFaila(
            "kietiakai_" + pavadinimas + ".txt",
            kietiakai
        ); });

    cout << "Isvedimas: "
         << isvedimas
         << " s\n";
}
void PaveldimumoTestas()
{
    // Zmogus z;
    // NEGALIMA - ABSTRACT CLASS

    Student s(
        "Jonas",
        "Jonaitis",
        {10, 9, 8},
        9);

    std::cout << "Paveldimumo testas OK\n";
}

void VectorBenchmark()
{
    const int sz = 1000000;

    // std::vector

    auto t1 = std::chrono::high_resolution_clock::now();

    std::vector<int> v1;

    for (int i = 0; i < sz; i++)
    {
        v1.push_back(i);
    }

    auto t2 = std::chrono::high_resolution_clock::now();

    // custom Vector

    auto t3 = std::chrono::high_resolution_clock::now();

    Vector<int> v2;

    for (int i = 0; i < sz; i++)
    {
        v2.push_back(i);
    }

    auto t4 = std::chrono::high_resolution_clock::now();

    std::cout
        << "std::vector: "
        << std::chrono::duration<double>(t2 - t1).count()
        << " s\n";

    std::cout
        << "Vector: "
        << std::chrono::duration<double>(t4 - t3).count()
        << " s\n";
}

int main()
{

    Vector<int> v;

    for (int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }

    std::cout << v.size() << std::endl;

    Testai();

    VectorBenchmark();

    PaveldimumoTestas();

    std::filesystem::create_directory("data");

    try
    {
        //  FAILŲ GENERAVIMAS 

        GeneruotiFaila(
            "data/studentai1000.txt",
            1000);

        GeneruotiFaila(
            "data/studentai10000.txt",
            10000);

        GeneruotiFaila(
            "data/studentai100000.txt",
            100000);

        GeneruotiFaila(
            "data/studentai1000000.txt",
            1000000);

        std::string failas =
            "data/studentai100000.txt";

        //  VECTOR 

        TestuotiKonteineri<
            Vector<Student>>(
            failas,
            "vector");

        //  LIST 

        TestuotiKonteineri<
            std::list<Student>>(
            failas,
            "list");

        //  DEQUE 

        TestuotiKonteineri<
            std::deque<Student>>(
            failas,
            "deque");
    }
    catch (const std::exception &e)
    {
        cout << "Klaida: "
             << e.what()
             << endl;
    }

    return 0;
}
