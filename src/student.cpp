#include "student.h"

#include <algorithm>
#include <numeric>
#include <utility>

//  PAGALBINES 

double Vidurkis(const std::vector<int>& paz)
{
    if (paz.empty()) return 0.0;

    int suma = std::accumulate(
        paz.begin(),
        paz.end(),
        0
    );

    return static_cast<double>(suma) / paz.size();
}

double Mediana(std::vector<int> paz)
{
    if (paz.empty()) return 0.0;

    std::sort(paz.begin(), paz.end());

    int n = paz.size();

    if (n % 2 == 0)
    {
        return (paz[n / 2 - 1] + paz[n / 2]) / 2.0;
    }

    return paz[n / 2];
}


//  KONSTRUKTORIAI 

Student::Student() : Zmogus(), egz_(0), rez_vid_(0.0), rez_med_(0.0)
{
}

Student::Student(
    const std::string& vardas,
    const std::string& pavarde
)
    : Zmogus(vardas, pavarde),
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
    : Zmogus(vardas, pavarde),
      paz_(paz),
      egz_(egz)
{
    SkaiciuotiGalutinius();
}

//  DESTRUKTORIUS 

Student::~Student()
{
}

//  COPY CONSTRUCTOR 

Student::Student(const Student& other)
    : Zmogus(other.vardas_, other.pavarde_),
      paz_(other.paz_),
      egz_(other.egz_),
      rez_vid_(other.rez_vid_),
      rez_med_(other.rez_med_)
{
}

//  COPY ASSIGNMENT 

Student& Student::operator=(const Student& other)
{
    if (this != &other)
    {
        vardas_ = other.vardas_;
        pavarde_ = other.pavarde_;

        paz_ = other.paz_;

        egz_ = other.egz_;

        rez_vid_ = other.rez_vid_;
        rez_med_ = other.rez_med_;
    }

    return *this;
}

//  MOVE CONSTRUCTOR 

Student::Student(Student&& other) noexcept
    : Zmogus(
        std::move(other.vardas_),
        std::move(other.pavarde_)
      ),
      paz_(std::move(other.paz_)),
      egz_(other.egz_),
      rez_vid_(other.rez_vid_),
      rez_med_(other.rez_med_)
{
}

//  MOVE ASSIGNMENT 

Student& Student::operator=(Student&& other) noexcept
{
    if (this != &other)
    {
        vardas_ = std::move(other.vardas_);
        pavarde_ = std::move(other.pavarde_);

        paz_ = std::move(other.paz_);

        egz_ = other.egz_;

        rez_vid_ = other.rez_vid_;
        rez_med_ = other.rez_med_;
    }

    return *this;
}

//  GETTERIAI 

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

//  SETTERIAI 

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

//  SKAICIAVIMAI 

void Student::SkaiciuotiGalutinius()
{
    double vid = Vidurkis(paz_);

    double med = Mediana(paz_);

    rez_vid_ = 0.4 * vid + 0.6 * egz_;

    rez_med_ = 0.4 * med + 0.6 * egz_;
}

//  OPERATORIAI 

std::ostream& operator<<(
    std::ostream& os,
    const Student& s
)
{
    os << s.vardas()
       << " "
       << s.pavarde()
       << " "
       << s.rez_vid();

    return os;
}

std::istream& operator>>(
    std::istream& is,
    Student& s
)
{
    std::string vardas;
    std::string pavarde;

    is >> vardas >> pavarde;

    s.setVardas(vardas);

    s.setPavarde(pavarde);

    return is;
}
