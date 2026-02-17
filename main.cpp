#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using std::cout;
using std::endl;
using std::setw;
using std::string;
using std::vector;
using std::left;
using std::right;
using std::cin;


struct Student
{
    std::string vardas = "A";
    std::string pavarde = "BB";
    //int paz, egz;  
    std::vector<int> paz = { 0 }; 
    int egz;
    double rez;
};

void Spausdinimas(const vector<Student> &grupe);

int main()
{
    Student A;
    vector<Student> grupe;
    for(int ii=0; ii<2; ii++)
    { 
        grupe.push_back(A);
    
    cout<<"Iveskite varda ir pavarde: ";
    cin>>A.vardas>>A.pavarde;
    //std::cout << A.vardas << " " << A.pavarde << std::endl;
    cout<<"Iveskite semestro pazymius:\nKiek pazymiu bus?";
    int n, temp, sum=0;
    cin>>n;
    for(int i=0; i<n; i++)
    {
        cout<<"Iveskite "<<i+1<<" pazymi: "<<n<<":"<<endl;
        cin>>temp;
        A.paz.push_back(temp);
        sum+=temp;
    }
    cout<<"Iveskite egzamino pazymi: ";
    cin>>A.egz;
    A.rez = (sum / n) * 0.4 + A.egz * 0.6;
    grupe.push_back(A);
    A.paz.clear();
    }
    Spausdinimas(grupe);
}
void Spausdinimas(const vector<Student> &grupe)
{
    for(auto A:grupe)
    {
        std::cout<<left<<setw(10)<<A.vardas<<right<<setw(10)<<A.pavarde<<endl;
        //for(auto a:A.paz) cout<<setw(3)<<a;
        //cout<<setw(10)<<A.egz<<endl;
        cout<<setw(20)<<A.rez<<endl;
    }
}