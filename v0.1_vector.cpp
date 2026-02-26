#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <random>
#include <limits>
#include <fstream>
#include <sstream>

using std::cin;
using std::cout;
using std::endl;
using std::left;
using std::right;
using std::setw;
using std::string;
using std::vector;

struct Student
{
    std::string vardas = "A";
    std::string pavarde = "BB";
    std::vector<int> paz;
    int egz = 0;
    double rez_vid = 0.0; 
    double rez_med = 0.0; 
};

double Mediana(vector<int> paz)
{
    if (paz.empty()) return 0.0;
    std::sort(paz.begin(), paz.end());
    int n = (int)paz.size();
    if (n % 2 == 0) return (paz[n / 2 - 1] + paz[n / 2]) / 2.0;
    return paz[n / 2];
}

double Vidurkis(const vector<int> &paz)
{
    if (paz.empty()) return 0.0;
    int sum = 0;
    for (int x : paz) sum += x;
    return static_cast<double>(sum) / paz.size();
}

int RandomPazymys(std::mt19937 &gen)
{
    static std::uniform_int_distribution<int> dist(1, 10);
    return dist(gen);
}

string RandomIsSaraso(const vector<string> &sar, std::mt19937 &gen)
{
    std::uniform_int_distribution<int> dist(0, (int)sar.size() - 1);
    return sar[dist(gen)];
}

void Spausdinimas(const vector<Student> &grupe, std::ostream &out)
{
    out << left << setw(15) << "Pavarde"
        << left << setw(15) << "Vardas"
        << right << setw(20) << "Galutinis (Vid.)"
        << right << setw(20) << "Galutinis (Med.)"
        << endl;

    out << string(70, '-') << endl;
    out << std::fixed << std::setprecision(2);

    for (const auto &A : grupe)
    {
        out << left << setw(15) << A.pavarde
            << left << setw(15) << A.vardas
            << right << setw(20) << A.rez_vid
            << right << setw(20) << A.rez_med
            << endl;
    }
}

bool NuskaitytiIsFailo(const string &failoVardas, vector<Student> &grupe)
{
    std::ifstream fin(failoVardas);
    if (!fin.is_open())
    {
        cout << "Nepavyko atidaryti failo: " << failoVardas << endl;
        return false;
    }

    string headerLine;
    std::getline(fin, headerLine);

    std::istringstream hs(headerLine);
    string tok;
    int nd_kiek = 0;
    while (hs >> tok)
        if (tok.rfind("ND", 0) == 0) nd_kiek++;

    Student A;
    while (fin >> A.vardas >> A.pavarde)
    {
        A.paz.clear();

        for (int i = 0; i < nd_kiek; i++)
        {
            int nd;
            fin >> nd;
            A.paz.push_back(nd);
        }

        fin >> A.egz;

        double vid = Vidurkis(A.paz);
        double med = Mediana(A.paz);

        A.rez_vid = 0.4 * vid + 0.6 * A.egz;
        A.rez_med = 0.4 * med + 0.6 * A.egz;

        grupe.push_back(A);
    }

    return true;
}

int main()
{
    Student A;
    vector<Student> grupe;

    char rezimas;
    cout << "Ivedimas ranka, atsitiktinis ar is failo? (r/a/f): ";
    cin >> rezimas;

    if (rezimas == 'f' || rezimas == 'F')
    {
        if (!NuskaitytiIsFailo("studentai.txt", grupe))
            return 0;

        char kur;
        cout << "Isvedimas i ekrana ar i faila? (e/f): ";
        cin >> kur;

        if (kur == 'f' || kur == 'F')
        {
            std::ofstream fout("rezultatai.txt");
            Spausdinimas(grupe, fout);
            cout << "Rezultatai issaugoti faile: rezultatai.txt\n";
        }
        else
        {
            Spausdinimas(grupe, std::cout);
        }

        return 0;
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    vector<string> vardai = {"Jonas", "Petras", "Mantas", "Lukas", "Tomas", "Ieva", "Austeja", "Greta", "Egle", "Monika"};
    vector<string> pavardes = {"Kazlauskas", "Jankauskas", "Petrauskas", "Stankevicius", "Vaitkus",
                               "Kazlauskaite", "Jankauskaite", "Petrauskaite", "Stankeviciute", "Vaitkute"};

    int kiek_studentu = 0;
    int sugeneruota = 0;
    int nd_kiek = 0;

    if (rezimas == 'a' || rezimas == 'A')
    {
        cout << "Kiek studentu generuoti? ";
        cin >> kiek_studentu;
        cout << "Kiek ND pazymiu generuoti kiekvienam studentui? ";
        cin >> nd_kiek;
    }

    while (true)
    {
        A.paz.clear();

        if (rezimas == 'a' || rezimas == 'A')
        {
            if (sugeneruota >= kiek_studentu) break;

            A.vardas = RandomIsSaraso(vardai, gen);
            A.pavarde = RandomIsSaraso(pavardes, gen);
            cout << "\nGeneruojamas studentas: " << A.vardas << " " << A.pavarde << endl;
        }
        else
        {
            cout << "\nIveskite pavarde (0 - baigti studentu ivedima): ";
            cin >> A.pavarde;
            if (A.pavarde == "0") break;

            cout << "Iveskite varda: ";
            cin >> A.vardas;
        }

        if (rezimas == 'a' || rezimas == 'A')
        {
            for (int i = 0; i < nd_kiek; i++)
                A.paz.push_back(RandomPazymys(gen));

            A.egz = RandomPazymys(gen);

            cout << "Sugeneruoti ND: ";
            for (int x : A.paz) cout << x << " ";
            cout << "\nSugeneruotas egz: " << A.egz << endl;

            sugeneruota++;
        }
        else
        {
            cout << "Iveskite ND pazymius (1 iki 10, 0 - baigti ND ivedima):\n";
            while (true)
            {
                int temp;
                cout << "ND: ";
                cin >> temp;

                if (temp == 0) break;

                if (temp < 1 || temp > 10)
                {
                    cout << "Klaida! Galima ivesti tik nuo 1 iki 10 (arba 0 baigti).\n";
                    continue;
                }
                A.paz.push_back(temp);
            }

            while (true)
            {
                cout << "Iveskite egzamino pazymi nuo 1 iki 10: ";
                cin >> A.egz;

                if (A.egz >= 1 && A.egz <= 10) break;
                cout << "Klaida! Egzamino pazymys turi buti nuo 1 iki 10.\n";
            }
        }

        double vid = Vidurkis(A.paz);
        double med = Mediana(A.paz);

        A.rez_vid = 0.4 * vid + 0.6 * A.egz;
        A.rez_med = 0.4 * med + 0.6 * A.egz;

        grupe.push_back(A);
    }

    char kur;
    cout << "Isvedimas i ekrana ar i faila? (e/f): ";
    cin >> kur;

    if (kur == 'f' || kur == 'F')
    {
        std::ofstream fout("rezultatai.txt");
        Spausdinimas(grupe, fout);
        cout << "Rezultatai issaugoti faile: rezultatai.txt\n";
    }
    else
    {
        Spausdinimas(grupe, std::cout);
    }

    return 0;
}