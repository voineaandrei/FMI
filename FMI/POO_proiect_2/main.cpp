#include <iostream>
#include "Game.h"
using namespace std;

int main()
{
    Game Shootout;
    Shootout.Show_Round();
    int NR, NR_decisiv = 1;
    cin>>NR;
    while (NR != 0 && NR_decisiv != 0)
    {
        NR_decisiv = Shootout.Simulate_Round();
        if (NR_decisiv == 1)
        {
            Shootout.Show_TotalHPRemaining();
            Shootout.Show_Map();
            cin>>NR;
        }
    }
    return 0;
}
