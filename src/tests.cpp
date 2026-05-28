#include "student.h"

#include <cassert>
#include <sstream>
#include <iostream>

void RunTests()
{
    Student a(
        "Jonas",
        "Jonaitis",
        {10,9,8},
        9
    );

    Student b(a);

    assert(b.vardas() == "Jonas");

    Student c(std::move(b));

    assert(c.vardas() == "Jonas");

    std::stringstream ss;

    ss << "Petras Petraitis";

    Student d;

    ss >> d;

    assert(d.vardas() == "Petras");

    std::cout << "Unit tests OK\n";
}