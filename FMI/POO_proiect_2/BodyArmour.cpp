#include "BodyArmour.h"
#include <iostream>

BodyArmour::BodyArmour(int arm, int i)
:_Armour(arm)
,_Special_Trait(i)
{
}

BodyArmour_1::BodyArmour_1(int arm, int i)
    :BodyArmour(arm, i)
{
}

BodyArmour_2::BodyArmour_2(int arm, int i)
    :BodyArmour(arm, i)
{
}

BodyArmour_3::BodyArmour_3(int arm, int i)
    :BodyArmour(arm, i)
{
}


void BodyArmour::Show_BodyArmourStats() const
{
    std::cout<<"Armour: "<<this->_Armour;
    std::cout<<"Special Trait: ---";
}

void BodyArmour_1::Show_BodyArmourStats() const
{
    std::cout<<"Armour: "<<this->_Armour<<"\n";
    std::cout<<"Special Trait: + 50 Maximum HP";
}

void BodyArmour_2::Show_BodyArmourStats() const
{
    std::cout<<"Armour: "<<this->_Armour<<"\n";
    std::cout<<"Special Trait: + 3 movement speed, + 5 field of view";
}

void BodyArmour_3::Show_BodyArmourStats() const
{
    std::cout<<"Armour: "<<this->_Armour<<"\n";
    std::cout<<"Special Trait: + 5 damage, + 10 critical strike chance";
}
