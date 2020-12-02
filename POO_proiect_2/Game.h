#ifndef GAME_H
#define GAME_H
#include "Map.h"
#include "Agents.h"
#include <math.h>

class Game
{
    public:
        Game();
        void Show_Round();
        int Simulate_Round();
        int inRange(Agents, int**);
        void isTargeting(Agents*, Agents**);
        void isMoving(Agents*);
        void Turn(Agents*);
        void Show_Map();
        void Show_TotalHPRemaining() const;
    private:
        Map _Harta;
        Agent1 _A;
        Agent2 _B;
        Agent3 _C;
};

#endif // GAME_H
