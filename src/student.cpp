#include "student.h"

#include <algorithm>

// ================= KONSTRUKTORIAI =================

Student::Student()
    : egz_(0),
      rez_vid_(0.0),
      rez_med_(0.0)
{
}

Student::Student(
    const std::string& vardas,
    const std::string& pavarde
)
    : vardas_(vardas),
      pavarde_(pavarde),
      egz_(0),
      rez_vid_(0.0),
      rez_med_(0.0)
{
}

Student::Student(
    const std::string& vardas,
    const std::string& pavarde,
    const std::vector<int>& paz,
    int egz
)
    : vardas_(vardas),
      pavarde_(pavarde),
      paz_(paz),
      egz_(egz)
{
    SkaiciuotiGalutinius();
}

// ================= DESTRUKTORIUS =================

Student::~Student()
{
}

// ================= GETTERIAI =================

std::string Student::vardas() const
{
    return vardas_;
}

std::string Student::pavarde() const
{
    return pavarde_;
}

std::vector<int> Student::paz() const
{
    return paz_;
}

int Student::egz() const
{
    return egz_;
}

double Student::rez_vid() const
{
    return rez_vid_;
}

double Student::rez_med() const
{
    return rez_med_;
}

// ================= SETTERIAI =================

void Student::setVardas(const std::string& v)
{
    vardas_ = v;
}

void Student::setPavarde(const std::string& p)
{
    pavarde_ = p;
}

void Student::setEgz(int egz)
{
    egz_ = egz;
}

void Student::addPaz(int paz)
{
    paz_.push_back(paz);
}

void Student::clearPaz()
{
    paz_.clear();
}

// ================= PAGALBINĖS =================

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

// ================= SKAIČIAVIMAI =================

void Student::SkaiciuotiGalutinius()
{
    double vid = Vidurkis(paz_);
    double med = Mediana(paz_);

    rez_vid_ = 0.4 * vid + 0.6 * egz_;
    rez_med_ = 0.4 * med + 0.6 * egz_;
}