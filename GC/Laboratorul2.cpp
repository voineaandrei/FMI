#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <utility>
#include <stdlib.h>

using namespace std;

struct Punct
{
    int x, y;
    Punct(int val1 = 0, int val2 = 0)
    {
        x = val1;
        y = val2;
    };
    Punct(const Punct& p)
    {
        x = p.x;
        y = p.y;
    }
    bool operator < (const Punct& p) const
    {
        if (x != p.x)
            return x < p.x;
        return y < p.y;
    };
    friend ostream& operator << (ostream& out, const Punct& B);
};

Punct p0;
ostream& operator<<(ostream& out, const Punct& B)
{
    out << B.x << " " << B.y;
    return out;
}
int distSq(Punct p1, Punct p2)
{
    return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}
int orientation(Punct p, Punct q, Punct r)
{
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (val == 0)
        return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}

int compare(const void *vp1, const void *vp2)
{
    Punct *p1 = (Punct *)vp1;
    Punct *p2 = (Punct *)vp2;

    int o = orientation(p0, *p1, *p2);
    if (o == 0)
        return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1; // daca pct sunt coliniare, il pune primu pe ala mai departe

    return (o == 2)? -1: 1;
}



int main()
{
    int i, n;
    Punct A;
    vector <Punct> v;
    cin >> n;
    v.reserve(n);
    for (i = 0; i < n; i++)
    {
        cin >> A.x >> A.y;
        v.push_back(A);
    }
    int ymin = v[0].y;
    int mini = 0;

    for (i = 1; i < v.size(); i++)
        if ( (v[i].y < ymin) || (ymin == v[i].y && v[i].x < v[mini].x) )
        {
            ymin = v[i].y;
            mini = i;
        }
    swap (v[0], v[mini]);
    p0 = v[0];

    qsort(&v[1],  v.size()-1, sizeof(Punct), compare);

    vector <Punct> sol;
    sol.reserve(n);
    sol.push_back(v[0]);
    for (i = 1; i < v.size(); i++)
    {
        while ( orientation(sol[sol.size()-2],sol[sol.size()-1],v[i]) != 2 && sol.size() > 1)
        {
            sol.pop_back();
        }
        sol.push_back(v[i]);
    }
    if (sol.size() == 2)
    {
        int i1 = 0, i2 = 0;
        for (i = 0; i < v.size(); i++)
        {
            if (!((v[i].x == sol[0].x && v[i].y == sol[0].y) || (v[i].x == sol[1].x && v[i].y == sol[1].y)))
            {
                if (i1 == 0)
                    i1 = i;
                else
                    i2 = i;
            }
        }
        printf("I = {(%d, %d), (%d, %d)}\n",sol[0].x,sol[0].y,sol[1].x,sol[1].y);
        printf("J = {(%d, %d), (%d, %d)}",v[i1].x,v[i1].y,v[i2].x,v[i2].y);
    }
    if (sol.size() == 3)
    {
        int j;
        int i1;
        bool ok;
        for (i = 0; i < v.size(); i++)
        {
            ok = true;
            for (j = 0; j < sol.size(); j++)
            {
                if (v[i].x == sol[j].x && v[i].y == sol[j].y)
                    ok = false;
            }
            if (ok == true)
            {
                break;
            }
        }
        printf("I = {(%d, %d), (%d, %d), (%d, %d)}",sol[0].x,sol[0].y,sol[1].x,sol[1].y,sol[2].x,sol[2].y);
        printf("J = {(%d, %d)}",v[i].x,v[i].y);
    }
    if (sol.size() == 4)
    {
        printf("I = {(%d, %d), (%d, %d)}",sol[0].x,sol[0].y,sol[2].x,sol[2].y);
        printf("J = {(%d, %d), (%d, %d)}",sol[1].x,sol[1].y,sol[3].x,sol[3].y);
    }
    return 0;
}
