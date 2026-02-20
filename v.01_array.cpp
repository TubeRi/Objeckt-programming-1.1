#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <random>

using std::cin;
using std::cout;
using std::endl;
using std::string;

struct Student
{
    string vardas;
    string pavarde;

    int *paz = nullptr; // C masyvas ND pažymiams
    int paz_kiek = 0;   // kiek ND
    int paz_cap = 0;    // talpa
    // maudojam cap , kad kiekkviena karta nereiktu didinti po 1, o dabar viksa dvigubinam 4 8 16
    int egz = 0;
    double rez = 0.0;
};

void AddPaz(Student &s, int x) //vector.push_back imitacija
{
    if (s.paz_kiek == s.paz_cap) // jeigu atmintis pilna reikia ja padidinti
    {
        int newCap = (s.paz_cap == 0) ? 4 : s.paz_cap * 2;
        int *naujas = new int[newCap]; // kuria nauja masyva

        for (int i = 0; i < s.paz_kiek; i++)
            naujas[i] = s.paz[i]; // copy old info ir perkeli i nauja masyva

        delete[] s.paz; // atlaisvinti sena masyva
        s.paz = naujas;
        s.paz_cap = newCap;
    }
    s.paz[s.paz_kiek++] = x; // naujas pazymys 
}

void clearStudent(Student &s) // rankinis valymas
{
    delete[] s.paz;
    s.paz = nullptr;
    s.paz_kiek = 0;
    s.paz_cap = 0;
}

void CopyStudentDeep(Student &dst, const Student &src) // rekomendacine funckija
{
    dst.vardas = src.vardas;  // daroma tvirtesne kopija, nes studentas yra dinamine atmintis
    dst.pavarde = src.pavarde;
    dst.egz = src.egz;
    dst.rez = src.rez;

    dst.paz_kiek = src.paz_kiek;
    dst.paz_cap = src.paz_kiek; // tik tiek, kiek reikia
    dst.paz = (dst.paz_kiek > 0) ? new int[dst.paz_cap] : nullptr;

    for (int i = 0; i < dst.paz_kiek; i++)
        dst.paz[i] = src.paz[i];
}

// studentu masyvo didinimas
void AddStudent(Student *&grupe, int &kiek, int &cap, const Student &s) // push.back
{
    if (kiek == cap)
    {
        int newCap = (cap == 0) ? 4 : cap * 2;
        Student *nauja = new Student[newCap]; // naujas masyvas

        // perkeliame senus studentus
        for (int i = 0; i < kiek; i++)
        {
            CopyStudentDeep(nauja[i], grupe[i]); // isvalo sena atminti
            clearStudent(grupe[i]); // istrina sena masyva
        }

        delete[] grupe;
        grupe = nauja; // naujas ptr
        cap = newCap;
    }

    // įdedame naują studentą
    CopyStudentDeep(grupe[kiek], s);
    kiek++;
}

double Vidurkis(const Student &s)
{
    if (s.paz_kiek == 0)
        return 0.0;
    int sum = 0;
    for (int i = 0; i < s.paz_kiek; i++)
        sum += s.paz[i];
    return static_cast<double>(sum) / s.paz_kiek;
}

double Mediana(const Student &s)
{
    if (s.paz_kiek == 0)
        return 0.0;

    // kopijuojam į laikiną masyvą ir rikiuojam
    int n = s.paz_kiek;
    int *tmp = new int[n];
    for (int i = 0; i < n; i++)
        tmp[i] = s.paz[i];

    std::sort(tmp, tmp + n);

    double med;
    if (n % 2 == 0)
        med = (tmp[n / 2 - 1] + tmp[n / 2]) / 2.0;
    else
        med = tmp[n / 2];

    delete[] tmp;
    return med;
}
int RandomPazymys(std::mt19937 &gen)
{
    static std::uniform_int_distribution<int> dist(1, 10);
    return dist(gen);
}
void Spausdinimas(const Student *grupe, int kiek, char pasirinkimas)
{
    cout << std::left << std::setw(15) << "Pavarde"
         << std::left << std::setw(15) << "Vardas";

    if (pasirinkimas == 'v' || pasirinkimas == 'V')
        cout << std::right << std::setw(20) << "Galutinis (Vid.)" << "\n";
    else
        cout << std::right << std::setw(20) << "Galutinis (Med.)" << "\n";

    cout << string(50, '-') << "\n";
    cout << std::fixed << std::setprecision(2);

    for (int i = 0; i < kiek; i++)
    {
        cout << std::left << std::setw(15) << grupe[i].pavarde
             << std::left << std::setw(15) << grupe[i].vardas
             << std::right << std::setw(20) << grupe[i].rez
             << "\n";
    }
}

int main()
{
    char pasirinkimas;
    cout << "Skaiciuoti galutini pagal vidurki ar mediana? (v/m): ";
    cin >> pasirinkimas;

    char rezimas;
    cout << "Ivedimas ranka ar atsitiktinis? (r/a): ";
    cin >> rezimas;

    std::random_device rd;
    std::mt19937 gen(rd());

    // Grupė kaip C masyvas
    Student *grupe = nullptr;
    int kiek = 0;
    int cap = 0;

    // Įvedimas: m nežinomas -> iki pavardė "0"
    while (true)
    {
        Student s; // laikinas studentas

        cout << "\nIveskite pavarde (0 - baigti studentu ivedima): ";
        cin >> s.pavarde;
        if (s.pavarde == "0")
        {
            clearStudent(s);
            break;
        }

        cout << "Iveskite varda: ";
        cin >> s.vardas;

        if (rezimas == 'a' || rezimas == 'A')
        {
            int nd_kiek;
            cout << "Kiek ND generuoti? ";
            cin >> nd_kiek;

            for (int i = 0; i < nd_kiek; i++)
                AddPaz(s, RandomPazymys(gen));
            s.egz = RandomPazymys(gen);

            cout << "Sugeneruoti ND: ";
            for (int i = 0; i < s.paz_kiek; i++)
                cout << s.paz[i] << " ";
            cout << "\nSugeneruotas egz: " << s.egz << "\n";
        }
        else
        {
            cout << "Iveskite ND pazymius (0 - baigti ND ivedima):\n";
            while (true)
            {
                int x;
                cout << "ND (nuo 1 iki 10, 0 - baigti): ";
                cin >> x;

                if (x == 0)
                    break;

                if (x < 1 || x > 10)
                {
                    cout << "Klaida! Iveskite skaiciu nuo 1 iki 10.\n";
                    continue;
                }

                AddPaz(s, x);
            }

            while (true)
            {
                cout << "Iveskite egzamino pazymi nuo 1 iki 10: ";
                cin >> s.egz;

                if (s.egz >= 1 && s.egz <= 10)
                    break;

                cout << "Klaida! Egzamino pazymys turi buti nuo 1 iki 10.\n";
            }
        }

        double vid = Vidurkis(s);
        double med = Mediana(s);

        if (pasirinkimas == 'v' || pasirinkimas == 'V')
            s.rez = 0.4 * vid + 0.6 * s.egz;
        else
            s.rez = 0.4 * med + 0.6 * s.egz;

        AddStudent(grupe, kiek, cap, s);

        // atlaisvinam laikino studento vidinius resursus
        clearStudent(s);
    }

    cout << "\n";
    Spausdinimas(grupe, kiek, pasirinkimas);

    // atlaisvinam visos grupės atmintį
    for (int i = 0; i < kiek; i++)
        clearStudent(grupe[i]);
    delete[] grupe;

    return 0;
}
