#ifndef AGENTS_H
#define AGENTS_H
#include "Gun.h"
#include "BodyArmour.h"

// Se cheama Agents, dar initializeaza doar unul
// Din pacate a trebuit sa fac mai multi agenti derivati, desi nu am vrut sa fac acest lucru. Am incercat sa dau fiecarui
// jucator o arma si o armura random, dar de fiecare data cand faceam acest lucru, toti playerii primeau aceeasi arma si
// aceeasi armura, iar statisticile bonus de la o armura se aplicau pt toti playerii
// Din aceasta cauza am 3 clase derivate.. cam degeaba

class Agents
{
public:
    Agents(char = ' ', int = -1, int = -1, int hp = 100, int fov = 11, int ms = 5);
    virtual ~Agents();
    virtual void Show_Stats() const;
    virtual bool isAlive();
    Agents& operator - (const Agents& Aux); // nu le-am folosit, deoarece le-am implementat foarte tarziu
    Agents& operator = (const Agents& Aux); // si mi-a fost frica sa le folosesc

    friend class Game;
protected:
    int _HP; // health points
    int _FOV; // field of view
    int _MovementSpeed;
    char _Name;
    int _CurrentX, _CurrentY;
    Gun* _gun;
    BodyArmour* _armour;
};

class Agent1 : public Agents
{
public:
    Agent1(char = 'A', int = -1, int = -1, int hp = 100, int fov = 11, int ms = 5);
    ~Agent1();
    void Show_Stats() const;
    bool isAlive();

};

class Agent2 : public Agents
{
public:
    Agent2(char = 'B', int = -1, int = -1, int hp = 100, int fov = 11, int ms = 5);
    ~Agent2();
    void Show_Stats() const;
    bool isAlive();

};

class Agent3 : public Agents
{
public:
    Agent3(char = 'C', int = -1, int = -1, int hp = 100, int fov = 11, int ms = 5);
    ~Agent3();
    void Show_Stats() const;
    bool isAlive();

};
#endif // AGENTS_H
