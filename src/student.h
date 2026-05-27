#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>

class Student
{
private:

    std::string vardas_;
    std::string pavarde_;

    std::vector<int> paz_;

    int egz_;

    double rez_vid_;
    double rez_med_;

public:

    // ================= KONSTRUKTORIAI =================

    Student();

    Student(
        const std::string& vardas,
        const std::string& pavarde
    );

    Student(
        const std::string& vardas,
        const std::string& pavarde,
        const std::vector<int>& paz,
        int egz
    );

    // ================= DESTRUKTORIUS =================

    ~Student();

    // ================= GETTERIAI =================

    std::string vardas() const;
    std::string pavarde() const;

    std::vector<int> paz() const;

    int egz() const;

    double rez_vid() const;
    double rez_med() const;

    // ================= SETTERIAI =================

    void setVardas(const std::string& v);
    void setPavarde(const std::string& p);

    void setEgz(int egz);

    void addPaz(int paz);

    void clearPaz();

    // ================= SKAIČIAVIMAI =================

    void SkaiciuotiGalutinius();
};

#endif