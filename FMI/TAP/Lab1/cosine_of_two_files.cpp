#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string.h>

using namespace std;

int main()
{
    ifstream f("fisier1.in");
    ifstream g("fisier2.in");
    char line[200], *p;
    vector <string> c;
    int fr1[200] = {0}, fr2[200] = {0}, i, ok;
    // intram in primu fisier
    while (!f.eof())
    {
        // luam o linie
        f.getline(line,200);
        // despartim cuvintele
        p = strtok(line, "., ");
        while(p)
        {
            // ok = 0, nu a mai fost cuvantul si il adaugam
            // ok = 1, a mai fost cuvantul si doar il numaram
            ok =0;
            for (i = 0; i < c.size(); i++)
                if (p == c[i])
                    {
                        fr1[i]++;
                        ok = 1;
                    }
                if (ok == 0)
                    {
                        c.push_back(p);
                        fr1[c.size()-1]++;
                    }
            p = strtok(NULL, "., ");
        }
    }
    // analog g
    while (!g.eof())
    {
        g.getline(line, 200);
        p = strtok(line, "., ");
        while (p)
        {
            ok =0;
            for (i = 0; i < c.size(); i++)
                if (p == c[i])
                    {
                        fr2[i]++;
                        ok = 1;
                    }
                if (ok == 0)
                    {
                        c.push_back(p);
                        fr2[c.size()-1]++;
                    }
            p = strtok(NULL, "., ");
        }
    }
    // calculele dupa teorema
    int numarator = 0, rad1 = 0, rad2 = 0;
    for (i = 0; i < c.size(); i++)
    {
        numarator += fr1[i] * fr2[i];
        rad1 += fr1[i] * fr1[i];
        rad2 += fr2[i] * fr2[i];
    }
    float dcos = 1.0*numarator/(sqrt(rad1)*sqrt(rad2));
    cout << dcos;
    return 0;
}
