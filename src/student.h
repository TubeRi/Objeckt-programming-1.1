#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <iostream>
#include "zmogus.h"

class Student : public Zmogus
{
private:
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

    // ================= RULE OF FIVE =================

    ~Student();

    Student(const Student& other);
    Student& operator=(const Student& other);

    Student(Student&& other) noexcept;
    Student& operator=(Student&& other) noexcept;

    // ================= GETTERIAI =================

    std::vector<int> paz() const;
    int egz() const;
    double rez_vid() const;
    double rez_med() const;

    // ================= SETTERIAI =================

    void setEgz(int egz);
    void addPaz(int paz);
    void clearPaz();

    // ================= SKAIČIAVIMAI =================

    void SkaiciuotiGalutinius() override;

    // ================= OPERATORIAI =================

    friend std::ostream& operator<<(std::ostream& os, const Student& s);
    friend std::istream& operator>>(std::istream& is, Student& s);
};

#endif