#ifndef BODYARMOUR_H
#define BODYARMOUR_H
#define Tank 1
#define IamSpeed 2
#define Berserk 3
#include <stdlib.h>
#include <time.h>

// Actual traits (mai usor de implementat):
// 1 -> + 50 (Max) HP
// 2 -> + 3 movement speed, + 5 FOV
// 3 -> + 5 damage, + 10 Critical Strike Chance

class BodyArmour
{
public:
    BodyArmour(int = 100, int = rand()%4+1);
    virtual void Show_BodyArmourStats() const;
    virtual int GetSpecialTrait() const {return _Special_Trait;};

    friend class Agents;
    friend class Game;

protected:
    int _Armour;
    int _Special_Trait;
};

class BodyArmour_1: public BodyArmour
{
public:
    BodyArmour_1(int = 100, int = 1);
    void Show_BodyArmourStats() const;
    int GetSpecialTrait() const {return _Special_Trait;};
};

class BodyArmour_2: public BodyArmour
{
public:
    BodyArmour_2(int = 100, int = 2);
    void Show_BodyArmourStats() const;
    int GetSpecialTrait() const {return _Special_Trait;};
};

class BodyArmour_3: public BodyArmour
{
public:
    BodyArmour_3(int = 100, int = 3);
    void Show_BodyArmourStats() const;
    int GetSpecialTrait() const {return _Special_Trait;};
};

#endif // BODYARMOUR_H
