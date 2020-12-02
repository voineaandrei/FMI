#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Complexitate: O(n log n) ( sortare in n log n + parcurgerea vectorului v in O (n) )
/* Corectitudine:
Sortam cuburile dupa lungime. Presupunem ca solutia optima incepe de al doilea cub(notat X), sarind peste cel mai mare cub(notat C).
Daca C are aceeasi culoare ca si X, atunci putem observa ca inlocuid pe X cu C in solutie, obtinem o solutie mai buna, deci
presupunerea este gresita. Contradictie.
Daca C are culoare diferita fata de X, atunci il putem pune inainte de X, deoarece C are lungimea mai mare decat X si culoare diferita,
rezultand astfel intr-o solutie mai buna, deci contradictie.
Prin inductie, aplicam aceasta idee la fiecare pas.
*/

struct cub
{
    int lungime, culoare, index;
    bool operator < (const cub b)
    {
        return lungime > b.lungime;
    }
};

int main()
{
    int n, i, j, p;
    int lung, cul;
    vector <cub> v;
    v.reserve(n);

    cin >> n >> p; // nr cuburi | nr culori
    for (i = 0; i < n; i++)
    {
        cin >> lung >> cul;
        v.push_back(cub{lung, cul, i+1});
    }

    sort(v.begin(), v.end());

    vector <cub> sol;
    sol.reserve(n);
    sol.push_back(v[0]);
    lung = sol[0].lungime;

    // incepem prin a pune in vectorul de solutii cubul de cea mai mare lungime
    // verificam urmatoarele cuburi, iar daca cubul la "care ne uitam" (v[i]) are culoare diferita
    // fata de ultimul cub din vectorull de solutii, il adaugam in vectorul respectiv

    for (i = 1; i < v.size(); i++)
    {
        if (sol[sol.size()-1].culoare != v[i].culoare)
            {
                sol.push_back(v[i]);
                lung += v[i].lungime;
            }
    }

    cout << sol.size() << " " << lung << endl;
    for (i = 0; i < sol.size(); i++)
            cout << sol[i].index << " ";

    return 0;
}
