#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <random>
#include <limits>
#include <fstream>


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
    // int paz, egz;
    std::vector<int> paz;
    int egz = 0;
    double rez = 0.0;
};
double Mediana(vector<int> paz)
{
    // is bedos galima ir optimizuoti geriau
    // imama kopija
    if (paz.empty()) // tikrina ar tuscias
        return 0.0;
    std::sort(paz.begin(), paz.end()); // surikiuoja didejimo tvarka, suteikia 1 ir uz paskutinio
    int n = (int)paz.size();
    if (n % 2 == 0)
        return (paz[n / 2 - 1] + paz[n / 2]) / 2.0;
    else
        return paz[n / 2];
}
// vid funkcija, jog nereiktu sum ir n laikyti atskirai
double Vidurkis(const vector<int> &paz)
{
    if (paz.empty())
        return 0.0; // tikrina ar tuscias
    int sum = 0;
    for (int x : paz)
        sum += x;
    return static_cast<double>(sum) / paz.size();
}
int RandomPazymys(std::mt19937 &gen) // standartinis rabdom gen, geresnis negu rand
{
    static std::uniform_int_distribution<int> dist(1, 10); // sukuriamas viena karta, lieka atmintyje
    return dist(gen); // greitas
    // int x = rd(); butu neefektyvu ir per letas
    // gen --> generuoja skaicius
    // dist -> perkelia i intervala
}

/** 
int limitas(const std::string& prompt, int minVal, int maxVal, bool leistiNuli)
{
    int x;

    while (true)
    {
        cout << prompt;

        if (!(cin >> x))
        {
            // Blogai ivede, ignoruoja ir praso is naujo
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Klaida! Iveskite tik skaiciu.\n";
            continue;
        }

        if (leistiNuli && x == 0) return 0;

        if (x < minVal || x > maxVal)
        {
            cout << "Klaida! Iveskite skaiciu nuo " << minVal << " iki " << maxVal;
            if (leistiNuli) cout << " (arba 0 - baigti)";
            cout << ".\n";
            continue;
        }

        return x;
    }
}
**/
string RandomIsSaraso(const vector<string> &sar, std::mt19937 &gen)
{
    std::uniform_int_distribution<int> dist(0, (int)sar.size() - 1);
    return sar[dist(gen)];
}

void Spausdinimas(const vector<Student> &grupe, char pasirinkimas);

int main()
{
    Student A;
    vector<Student> grupe;

    char pasirinkimas;
    cout << "Skaiciuoti galutini pagal vidurki ar mediana? (v/m): ";
    cin >> pasirinkimas;

    char rezimas;
    cout << "Ivedimas ranka ar atsitiktinis? (r/a): ";
    cin >> rezimas;

    std::random_device rd; // sukuria pradini skaiciu, seed angliskai AI paaiskinimas
    std::mt19937 gen(rd()); // mt19937 – Mersenne Twister algoritmas. AI help :)
    // int x = rd(); butu neefektyvu ir per letas

    vector<string> vardai = {"Jonas", "Petras", "Mantas", "Lukas", "Tomas", "Ieva", "Austeja", "Greta", "Egle", "Monika"};
    vector<string> pavardes = {"Kazlauskas", "Jankauskas", "Petrauskas", "Stankevicius", "Vaitkus", "Kazlauskaite", "Jankauskaite", "Petrauskaite", "Stankeviciute", "Vaitkute"};

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
            if (sugeneruota >= kiek_studentu)
                break;

            A.vardas = RandomIsSaraso(vardai, gen);
            A.pavarde = RandomIsSaraso(pavardes, gen);
            cout << "\nGeneruojamas studentas: " << A.vardas << " " << A.pavarde << endl;
        }
        else
        {
            cout << "\nIveskite pavarde (0 - baigti studentu ivedima): ";
            cin >> A.pavarde;
            if (A.pavarde == "0")
                break;

            cout << "Iveskite varda: ";
            cin >> A.vardas;
        }

        if (rezimas == 'a' || rezimas == 'A')
        {
            // random num generator
            for (int i = 0; i < nd_kiek; i++)
                A.paz.push_back(RandomPazymys(gen));

            A.egz = RandomPazymys(gen);

            // parodo sugeneruotus pazymius, bet manrods nebutina
            cout << "Sugeneruoti ND: ";
            for (int x : A.paz)
                cout << x << " ";
            cout << "\nSugeneruotas egz: " << A.egz << endl;

            // PRIDĖTA: padidinam sugeneruotų studentų skaičių
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

                if (temp == 0)
                    break;

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

                if (A.egz >= 1 && A.egz <= 10)
                    break;

                cout << "Klaida! Egzamino pazymys turi buti nuo 1 iki 10.\n";
            }

            // cout << "Iveskite egzamino pazymi: ";
            // cin >> A.egz;
        }

        double vid = Vidurkis(A.paz);
        double med = Mediana(A.paz);

        if (pasirinkimas == 'v' || pasirinkimas == 'V')
            A.rez = 0.4 * vid + 0.6 * A.egz;
        else
            A.rez = 0.4 * med + 0.6 * A.egz;

        grupe.push_back(A);
    }
    Spausdinimas(grupe, pasirinkimas);
    return 0;
}

void Spausdinimas(const vector<Student> &grupe, char pasirinkimas)
{
    cout << left << setw(15) << "Pavarde"
         << left << setw(15) << "Vardas";

    if (pasirinkimas == 'v' || pasirinkimas == 'V')
        cout << right << setw(20) << "Galutinis (Vid.)" << endl;
    else
        cout << right << setw(20) << "Galutinis (Med.)" << endl;

    cout << string(50, '-') << endl;

    cout << std::fixed << std::setprecision(2);

    for (auto A : grupe)
    {
        std::cout << left << setw(15) << A.pavarde << left << setw(15) << A.vardas << right << setw(20) << A.rez << endl;

        // for(auto a:A.paz) cout<<setw(3)<<a;
        // cout<<setw(10)<<A.egz<<endl;
    }
}