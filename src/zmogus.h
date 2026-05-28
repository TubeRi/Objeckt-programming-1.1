#ifndef ZMOGUS_H
#define ZMOGUS_H

#include <string>

class Zmogus
{
protected:

    std::string vardas_;
    std::string pavarde_;

public:

    Zmogus();

    Zmogus(
        const std::string& vardas,
        const std::string& pavarde
    );

    virtual ~Zmogus();

    virtual void SkaiciuotiGalutinius() = 0;

    std::string vardas() const;
    std::string pavarde() const;

    void setVardas(const std::string& v);
    void setPavarde(const std::string& p);
};

#endif