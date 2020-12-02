#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/* Complexitate: O(n^2), in O(n log n) folosind priority queue*/
/* Algoritm:
Ne intereseaza cel mai mare profit, deci ordonam descrescator dupa profit si descrescator dupa termen, in caz de egalitate (desi nu are relevanta).
Luam primul element din vectorul sortat si punem in vectorul de solutii pe pozitia v[termen-1].
Spre exemplu, daca primul element are profitul 5 3, il punem in vectorul de solutii, pe pozitia 2.
In cazul in care pozitia este ocupata, scadem indicele pana gasim un loc neocupat.
*/

/*Corectitudine:
Cum am spus si in sectiunea unde am descris algoritmul, ordonam descrescator dupa profit.
Deci, daca punem un element in vectorul de solutii, inseamna ca nu exista alt element cu profit mai mare, care poate fi pus pe acea pozitie (ignorand permutarile care nu schimba solutia optima).
Astfel, solutia pe care o creem va fi mereu optima.
*/

struct t
{
    int profit, termen, index;
    bool operator < (const t b)
    {
        if (profit != b.profit)
            return profit > b.profit;
        return termen > b.termen;
    }
};

int main()
{
    int n, i;
    cin >> n;
    vector <t> v(n);
    for (i = 0 ; i < n; i++)
    {
        cin >> v[i].profit >> v[i].termen;
        v[i].index = i+1;
    }
    sort (v.begin(), v.end());
    vector <t> sol(n);
    for (i = 0; i < n; i++)
    {
        sol[i].profit = 0;
        sol[i].index = 0;
        sol[i].termen = 0;
    }
    int t;
    for (i = 0; i < n; i++)
    {
        t = v[i].termen;
        while (t >= 0)
        {
            t--;
            if (sol[t].profit == 0)
            {
                sol[t] = v[i];
                break;
            }
        }
    }
    int sum = 0;
    for (i = 0; i < n; i++)
        sum += sol[i].profit;
    cout << sum << endl;
    for (i = 0; i < n; i++)
        if (sol[i].profit != 0)
        cout << sol[i].index << " ";
    return 0;
}
