#ifndef IO_H
#define IO_H

#include "student.h"
#include <vector>
#include <string>
#include <ostream>

void Spausdinimas(std::vector<Student> grupe, char rikiavimas, std::ostream& out);
void FailoSkaitymas(const std::string& failoVardas, std::vector<Student>& grupe);

#endif