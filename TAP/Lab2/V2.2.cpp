#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/* Complexitate:
a) O (n log n), doar o sortare
b) O (n log n), daca n >= p
si O (n * p), daca p < n
*/
/* Corectitudine:
a) Dupa formula data (suma (f[i])(lung[1] +...lung[i])), putem observa ca trebuie sa ordonam textele descrescator dupa frecventa,
iar in cazul in care 2 frecvente sunt egale, le ordonam crescator in functie de lungime.
Pe un exemplu numeric:
2 limbaje: 100 1 si 50 2 (unde 100 si 50 sunt lungimile, iar 1 si 2 frecventele)
Daca am avea pe prima pozitie limbajul cu frecventa 1, ca sa citeasca textul suma va fi 100 * 1 + (100 + 50) * 2 = 400
In schimb, daca avem pe prima pozitie limbajul cu frecventa 2, suma va fi 50 * 2 + (100 + 50) * 1 = 250
Deci, ordonarea descrescatoare dupa frecventa si crescatoare dupa lungime in caz de egalitate ne da solutia optima.

b) Ordonam descrescator elementele. Presupunem ca sunt p benzi si n > p. Punem primele p texte pe cele p benzi.
Presupunem ca solutia optima consta in punerea urmatorului text pe oricare din cele p benzi, mai putin cea cu suma minima.
Putem observa ca daca am muta textul de pe acea banda pe banda cu suma minima, obtinem o solutie mult mai buna, deci contradictie.
Cu inductie, cum am facut cu elementul p+1, facem si cu elementul p+2, pana ajungem la elementul n, rezultand astfel solutia optima.
*/

/*Explicatie b)

Algoritmul va pune la inceputul fiecarei benzi cate un text. Va verifica pe ce banda se gaseste cel mai mic timp de acces (suma lungimilor textelor),
iar acolo va pune urmatorul text. Se repeta acest pas pana cand nu mai sunt texte de pus.

Avem o matrice unde fiecare element m[i][j] are 3 valori:
- lungime, care reprezinta lungimea textului
- suma_elem, care reprezinta suma elementelor pana in acel punct (v[0].lungime + v[1].lungime + .. + v[i].lungime)
- lungime_actuala, unde calculam cat dureaza pana citeste textul de pe pozitia k, cu formula folosita la subpunctul a, fiecare limbaj avand frecventa 1.
Vectorul indice_final reprezinta ultimul element de pe fiecare banda, spre exemplu daca indice_final[2] = 5, inseamna ca ultima valoare nenula de pe banda 2 se afla pe pozitia 5.

EXEMPLU GRESIT: Daca textele ar fi ordonate crescator, putem sa avem cazuri in care algoritmul da gres, precum:
Avem 4 texte de lungime 10, 6, 5, 1 si 2 benzi. Daca le-am pune in ordine crescatoare, prima banda va avea valoare 1, iar a doua 5. Conform algoritmului, va pune 6 pe prima banda (banda cu 1), deoarece 1 < 5 si 10 pe a doua banda.
Astfel, va rezulta banda 1: 1, 6 si banda 2: 5, 10, ceea ce este gresit. Rezultatul corect era banda 1: 1, 10 si banda 2: 5, 6.

Ordonam textele descrescator, ca sa le putem pune pe cele p benzi diferite.
Dupa ce atribuim fiecarei benzi cate un text, facem un for de la p la n. (de la p, deoarece am folosit primele p texte)
In for verificam de fiecare data ce banda are cea mai mica suma, iar pe aceea punem textul la care suntem in acel pas.

La final, afisam elemente de la capat la inceput, deoarece conform formulei de la subpunctul a este mai eficient ca pe o banda sa avem textele ordonate crescator.
*/
struct textA
{
    int lungime, frecventa;
    bool operator < (const textA A2)
    {
        if (frecventa != A2.frecventa)
            return frecventa > A2.frecventa;
        return lungime < A2.lungime;
    }
};

struct textB
{
    int lungime;
    int suma_elem, lungime_actuala;
    bool operator < (const textB b)
    {
        return lungime > b.lungime;
    }
    friend ostream& operator << (ostream& out, const textB b);
};

ostream& operator << (ostream& out, const textB b)
{
    out << b.lungime;
    return out;
}
int main()
{
    char ch;
    cout << "Ce subpunct se rezolva?" << endl;
    cin >> ch;
    while (ch != 'a' && ch != 'A' && ch != 'b' && ch!= 'B')
    {
        cout << "Caracterul trebuie sa fie ori 'a' ori 'b'" << endl;
        cin >> ch;
    }
    if (ch == 'a' || ch == 'A')
    {
        int n, i, lung, frec;
        cin >> n;
        vector <textA> t(n);
        for (i = 0; i < n; i++)
            cin >> t[i].lungime >> t[i].frecventa;

        sort(t.begin(), t.end());
        for (i = 0; i < n; i++)
            cout << t[i].lungime << " " << t[i].frecventa << endl;
        return 0;
    }
    else
    {
        int n, p, i, j;
        cin >> n >> p; // cate texte sunt si cate benzi sunt
        vector <int> t(n);
        for (i = 0; i < n; i++)
            cin >> t[i]; // lungimea fiecarui text
        sort(t.begin(), t.end(), greater<int>());

        textB banda[p][n];

        if (p > n) // daca avem mai multe benzi decat texte
        {
            for (i = 0; i < n; i++)
            {
                banda[i][0].lungime = t[i];
                banda[i][0].suma_elem = t[i];
                banda[i][0].lungime_actuala = t[i];
            }
            for (i = n; i < p; i++)
            {
                banda[i][0].lungime = 0;
                banda[i][0].suma_elem = 0;
                banda[i][0].lungime_actuala = 0;
            }
            for (i = 0; i < p; i++)
                cout << "Banda cu numarul " << i+1 << ": " << banda[i][0] << endl;
            return 0;
        }

        for (i = 0; i < p; i++)
        {
            banda[i][0].lungime = t[i];
            banda[i][0].suma_elem = t[i];
            banda[i][0].lungime_actuala = t[i];
        }
        vector <int> indice_final(p,0);
        int poz, sum_min;
        for (i = p; i < n; i++)
        {
            sum_min = banda[0][indice_final[0]].lungime_actuala;
            poz = 0;
            for (j = 1; j < p; j++)
            {
                if (sum_min > banda[j][indice_final[j]].lungime_actuala)
                {
                    sum_min = banda[j][indice_final[j]].lungime_actuala;
                    poz = j;
                }
            }
            indice_final[poz]++;
            banda[poz][indice_final[poz]].lungime = t[i];
            banda[poz][indice_final[poz]].suma_elem = banda[poz][indice_final[poz]-1].suma_elem + t[i];
            banda[poz][indice_final[poz]].lungime_actuala = banda[poz][indice_final[poz]].suma_elem + banda[poz][indice_final[poz]-1].lungime_actuala;
        }
        for (i = 0; i < p; i++)
        {
            cout << "Banda cu numarul " << i+1 << ": ";
            for (j = indice_final[i]; j >= 0; j--)
                cout << banda[i][j] << " ";
            cout << endl;
        }
    }
    return 0;
}
