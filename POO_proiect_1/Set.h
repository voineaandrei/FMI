#include <stdlib.h>
#include <iostream>
using namespace std;

class Set
{
    public:
    int Numar;      // Numarul elementelor
    int *Multime;   // Multimea propriu zisa
public:
    Set();
    Set(const Set&);
    ~Set();
    void Inserare(int);  // Inserarea numarului la sfarsitul vectorului
    void Stergere(int);  // Stergerea unui numar
    int Cautare(int);    // Cautarea unui numar
    void Proprietate();  // Proprietatea ca un numar sa se gaseasca doar o singura data in vector + ORDONEAZA VECTORUL
    void Ordonare(int*,int,int);     // qsort
    void Afisare();
    void Numere_Pare_Impare();
    int GetNumar();      // return Numar;
    int* GetMultime();   // return *Multime;
    Set& operator = (const Set& Aux);
    Set operator + (const Set& Aux);
    int operator < (const Set& Aux);
    int operator > (const Set& Aux);
    int operator [] (int index);     // Primul element sta pe pozitia 0
    Set operator * (int scalar);
    friend ostream& operator<<(ostream&, const Set&);
    friend istream& operator>>(istream&, Set&);
    int Suma();
};
