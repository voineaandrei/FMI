#ifndef GUN_H
#define GUN_H
#include <iostream>
#include <string>
using namespace std;

class Gun
{
public:
    Gun(string = " ", int = 0, int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);
    virtual ~Gun();
    virtual void Show_GunStats() const;

    friend class Agents;
    friend class Agent1;
    friend class Agent2;
    friend class Agent3;
    friend class Game;

protected:
    const int _Mag_Size, _Fire_Rate, _Reload_Time;
    int _Mag, _Damage, _Critical_Strike_Chance, _Accuracy, _Effective_Range, _ReloadATM; //At the moment
    string _Name;
};

class Assault_Rifle: public Gun
{
public:
    Assault_Rifle(string = "Assault Rifle", int = 15, int = 8, int = 2, int = 5, int = 1, int = 90, int = 15);
    ~Assault_Rifle();
    void Show_GunStats() const;
};

class Sniper: public Gun
{
public:
    Sniper(string = "Sniper", int dmg = 70, int mag = 2, int FR = 1, int ER = 11, int RT = 2, int acc = 70, int CSC = 5);
    ~Sniper();
    void Show_GunStats() const;
};

class Shotgun: public Gun
{
public:
    Shotgun(string = "Shotgun", int dmg = 60, int mag = 4, int FR = 1, int ER = 3, int RT = 2, int acc = 85, int CSC = 5);
    ~Shotgun();
    void Show_GunStats() const;
};
#endif // GUN_H
