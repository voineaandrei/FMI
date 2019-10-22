#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct paralelipiped
{
    int L, l, h;
    friend ostream& operator << (ostream& out, const paralelipiped A);
    // sortare dupa L, l, respectiv h in ordinea asta
    // daca L1 == L2, sortam dupa l si tot asa
    bool operator < (const paralelipiped& A) const
    {
        if (L != A.L)
            return L < A.L;
        if (l != A.l)
            return l < A.l;
        return h < A.h;
    }

};

void ordonare_elemente(paralelipiped* A)
{
    if ((*A).L < (*A).l)
        swap ((*A).L, (*A).l);
    if ((*A).L < (*A).h)
        swap ((*A).L, (*A).h);
    if ((*A).l < (*A).h)
        swap ((*A).l, (*A).h);
}

ostream& operator << (ostream& out, const paralelipiped A)
{
    out << A.L << " " << A.l << " " << A.h;
    return out;
}

int main()
{
    vector <paralelipiped> v;
    int n, L, l, h, i;
    cin >> n;
    for (i = 0; i < n; i++)
    {
        cin >> L >> l >> h;
        v.push_back({L, l, h});
    }
    // ordonam astfel incat L sa fie cel mai mare numar, l al doilea cel mai mare numar, respectiv h cel mai mic numar
    for (i = 0; i < v.size(); i++)
        ordonare_elemente(&v[i]);
    // sortam
    sort(v.begin(), v.end());

    // teoretic nu ne intereseaza toate aranjamentele ce pot fi formate, deoarece chiar daca avem doua paralelipipede
    // (5,4,1) si (6,5,4) si putem forma (7,5,4), raza maxima tot de 2 este
    // in schimb la (5,4,1) si (5,4,3) => (5,4,4), unde raza a crescut de la 1,5 la 2
    // explicatia: daca la formarea noului paralelipiped, cea mai mica variabila din unu din paralelipipede
    // ramane neschimbata (este folosita pt noul paralelipiped)
    // atunci ea va fi cea mai mica variabila si in noul paralelipiped => diametrul
    // pe scurt, singurele modificari utile sunt daca variabile care raman neschimbate sunt primele doua cele mai mari numere
    // din ambele paralelipipede
    // (x1, y1, z1) si (x1, y1, z2) => (x1, y1, z1+z2) unde x1 >= y1 > z1 / z2

    for (i = 0; i < v.size()-1; i++)
    {
        if (v[i].L == v[i+1].L && v[i].l == v[i+1].l)
            v[i].h += v[i+1].h;
    }
    for (i = 0; i < v.size(); i++)
        ordonare_elemente(&v[i]);

    // pozitia paralelipipedului cu raza maxima
    // ne intereseaza cea mai mica variabila din triplet {L, l, h}, si anume h, pentru ca le ordonam pe linia anterioara
    int maxi = 0;
    for (i = 1; i < v.size(); i++)
        if (v[maxi].h < v[i].h)
            maxi = i;

    // Algoritmul are complexitatea O(n log n) din cauza sortarii.
    cout << "Raza maxima este de " << (float)v[maxi].h/2.0 << " si se gaseste in paralelipipedul (" << v[maxi] << ")";
    return 0;
}
