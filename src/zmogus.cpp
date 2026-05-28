#include "zmogus.h"

Zmogus::Zmogus()
    : vardas_(""),
      pavarde_("")
{
}

Zmogus::Zmogus(
    const std::string& vardas,
    const std::string& pavarde
)
    : vardas_(vardas),
      pavarde_(pavarde)
{
}

Zmogus::~Zmogus()
{
}

std::string Zmogus::vardas() const
{
    return vardas_;
}

std::string Zmogus::pavarde() const
{
    return pavarde_;
}

void Zmogus::setVardas(const std::string& v)
{
    vardas_ = v;
}

void Zmogus::setPavarde(const std::string& p)
{
    pavarde_ = p;
}