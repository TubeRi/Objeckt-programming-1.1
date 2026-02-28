#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <random>
#include <fstream>
#include <sstream>
#include <chrono>

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
    double rez_vid = 0.0; //vidurkis
    double rez_med = 0.0; // mediana
};

double Mediana(vector<int> paz) // ji gauna kopija (vector<int> paz), kad galėtų rūšiuoti nekeičiant originalo.
{
    if (paz.empty()) return 0.0;
    std::sort(paz.begin(), paz.end()); // surusiuoja didejimo tvarka pries skaiciuojant mediana
    int n = (int)paz.size();
    if (n % 2 == 0) return (paz[n / 2 - 1] + paz[n / 2]) / 2.0;
    return paz[n / 2];
}

double Vidurkis(const vector<int> &paz) // const kad funkcija nekeistu vektoriaus ir apersendas kad nereiktu kopijuoti viso vektoriaus
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

// universali funkcija kodo vykdymo laiko matavmui
/*
kaip veikia laiko skaiciavimo funckija.
1. pasirenkamas high.resolution_clock, tiksliausias laikrodis c++ kalboje
2. NUstatomas ir issaugomas funckijos vykdymo pradzios laikas
3. iskviecia arba vykdo musu turima funkcija f()
4. diff suskaiciuoja double sekundziu skirtuma tarp pabaigos ir pradzios
5. Galiausiai grazina esama laika kiek vykde viska
*/
template <typename Func>
double Laikas(Func&& f)
{
    using clock = std::chrono::high_resolution_clock;
    auto start = clock::now();
    f();
    auto end = clock::now();
    std::chrono::duration<double> diff = end - start;
    return diff.count();
}



void Spausdinimas(vector<Student> grupe, char rikiavimas, std::ostream &out) // prisidejo naujas rikiavimas
// naudojam grupes kopija jog nekeistume origalo grupes ir main
//std::ostream &out leidzia naudoti tiek std::cout, tiek std::ofstream, kad spausdintume i ekrana arba i faila
{
    auto byPavardeVardas = [](const Student& a, const Student& b) {
        if (a.pavarde != b.pavarde) return a.pavarde < b.pavarde;
        return a.vardas < b.vardas;
    };

    switch (rikiavimas)
    {
        case '1': // vardas
            std::sort(grupe.begin(), grupe.end(), [](const Student& a, const Student& b) {
                if (a.vardas != b.vardas) return a.vardas < b.vardas;
                return a.pavarde < b.pavarde;
            });
            break;

        case '2': // pavarde
            std::sort(grupe.begin(), grupe.end(), byPavardeVardas);
            break;

        case '3': // pagal vidurki (didėjimo tvarka)
            std::sort(grupe.begin(), grupe.end(), [&](const Student& a, const Student& b) {
                if (a.rez_vid != b.rez_vid) return a.rez_vid < b.rez_vid;
                return byPavardeVardas(a, b);
            });
            break;

        case '4': //pagal mediana (didėjimo tvarka)
            std::sort(grupe.begin(), grupe.end(), [&](const Student& a, const Student& b) {
                if (a.rez_med != b.rez_med) return a.rez_med < b.rez_med;
                return byPavardeVardas(a, b);
            });
            break;

        default: // jei neteisingas pasirinkimas – pagal pavarde
            std::sort(grupe.begin(), grupe.end(), byPavardeVardas);
            break;
    }

    out << left  << setw(18) << "Pavarde"
        << left  << setw(18) << "Vardas"
        << right << setw(20) << "Galutinis (Vid.)"
        << right << setw(20) << "Galutinis (Med.)"
        << endl;

    out << string(76, '-') << endl;
    out << std::fixed << std::setprecision(2);

    for (const auto &A : grupe)
    {
        out << left  << setw(18) << A.pavarde
            << left  << setw(18) << A.vardas
            << right << setw(20) << A.rez_vid
            << right << setw(20) << A.rez_med
            << endl;
    }
}

bool Failoskaitymas(const string &failoVardas, vector<Student> &grupe)
{
    std::ifstream fin(failoVardas);
    if (!fin.is_open())
    {
        cout << "Nepavyko atidaryti failo: " << failoVardas << endl;
        return false;
    }

    // Antraste
    string headerLine;
    std::getline(fin, headerLine); // paima failp pirma eilute ( headeri) varda pavarde nd1 nd2 egz

    // ND kiekis
    std::istringstream hs(headerLine);
    string tok;
    int nd_kiek = 0;
    while (hs >> tok)
        if (tok.rfind("ND", 0) == 0) nd_kiek++; // suzino kiek yra nd pazymiu

    Student A;
    while (fin >> A.pavarde >> A.vardas)
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
        if (!Failoskaitymas("studentai1000000.txt", grupe))
            return 0;
    }
    else
    {
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
    }

    char rikiavimas;
    cout << "\nRikiuoti pagal: vardas(1), pavarde(2), galutinis vidurkis(3), galutinis mediana(4): ";
    cin >> rikiavimas;

    char kur;
    cout << "Isvedimas i ekrana ar i faila? (e/f): ";
    cin >> kur;

    if (kur == 'f' || kur == 'F')
    {
        std::ofstream fout("rezultatai.txt");

        double t = Laikas([&](){
            Spausdinimas(grupe, rikiavimas, fout);
        });
        cout << "Rezultatai issaugoti faile: rezultatai.txt\n";
        cout << "Spausdinimas (i faila) uztruko: " << std::fixed << std::setprecision(6) << t << " s\n";
    }
    else
    {
        double t = Laikas([&](){
            Spausdinimas(grupe, rikiavimas, std::cout);
        });
        cout << "Spausdinimas (i ekrana) uztruko: " << std::fixed << std::setprecision(6) << t << " s\n";
    }

    return 0;
}