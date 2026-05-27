#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <filesystem>
#include <sstream>

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
        {10,9,8},
        9
    );

    // COPY CONSTRUCTOR
    Student b(a);

    // COPY ASSIGNMENT
    Student c;
    c = a;

    // MOVE CONSTRUCTOR
    Student d(std::move(a));

    // MOVE ASSIGNMENT
    Student e;
    e = std::move(b);

    // STREAM OPERATORIAI
    Student s;

    std::stringstream ss;

    ss << "Petras Petraitis";

    ss >> s;

    std::cout << s << std::endl;

    std::cout << "Visi testai OK\n";
}
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
         << pavadinimas
         << " ==========\n";


    // ================= SKAITYMAS =================

    double skaitymas = Laikas([&]()
    {
        FailoSkaitymas(failas, studentai);
    });

    cout << "Skaitymas: "
         << skaitymas
         << " s\n";


    // ================= STRATEGIJA 1 =================

    double strategija1 = Laikas([&]()
    {
        Strategija1(
            studentai,
            vargsiukai,
            kietiakai
        );
    });

    cout << "Strategija 1: "
         << strategija1
         << " s\n";


    // ================= STRATEGIJA 2 =================

    Container studentai2 = studentai;

    double strategija2 = Laikas([&]()
    {
        Strategija2(
            studentai2,
            vargsiukai
        );
    });

    cout << "Strategija 2: "
         << strategija2
         << " s\n";


    // ================= STRATEGIJA 3 =================

    Container studentai3 = studentai;

    double strategija3 = Laikas([&]()
    {
        Strategija3(
            studentai3,
            vargsiukai
        );
    });

    cout << "Strategija 3: "
         << strategija3
         << " s\n";


    // ================= IŠVEDIMAS =================

    double isvedimas = Laikas([&]()
    {
        IsvestiIFaila(
            "vargsiukai_" + pavadinimas + ".txt",
            vargsiukai
        );

        IsvestiIFaila(
            "kietiakai_" + pavadinimas + ".txt",
            kietiakai
        );
    });

    cout << "Isvedimas: "
         << isvedimas
         << " s\n";
}



int main()
{
    Testai();

    std::filesystem::create_directory("data");

    try
    {
        // ================= FAILŲ GENERAVIMAS =================

        GeneruotiFaila(
            "data/studentai1000.txt",
            1000
        );

        GeneruotiFaila(
            "data/studentai10000.txt",
            10000
        );

        GeneruotiFaila(
            "data/studentai100000.txt",
            100000
        );

        GeneruotiFaila(
            "data/studentai1000000.txt",
            1000000
        );


        std::string failas =
            "data/studentai100000.txt";


        // ================= VECTOR =================

        TestuotiKonteineri<
            std::vector<Student>
        >(
            failas,
            "vector"
        );


        // ================= LIST =================

        TestuotiKonteineri<
            std::list<Student>
        >(
            failas,
            "list"
        );


        // ================= DEQUE =================

        TestuotiKonteineri<
            std::deque<Student>
        >(
            failas,
            "deque"
        );
    }
    catch (const std::exception& e)
    {
        cout << "Klaida: "
             << e.what()
             << endl;
    }

    return 0;
}