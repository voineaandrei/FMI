#include "Agents.h"

Agents::Agents(char name, int x, int y, int hp, int fov, int ms)
    :_Name(name)
    ,_CurrentX(x)
    ,_CurrentY(y)
    ,_HP(hp)
    ,_FOV(fov)
    ,_MovementSpeed(ms)
{
    if (_CurrentX == -1 || _CurrentY == -1)
    {
        srand(time(NULL));
        _CurrentX = rand()%33;
        _CurrentY = rand()%33;
    }
}

Agent1::Agent1(char name, int x, int y, int hp, int fov, int ms)
    :Agents(name, x, y, hp, fov, ms)
{
    _gun = new Assault_Rifle();
    _armour = new BodyArmour_3();
    if (_armour->GetSpecialTrait() == 1)
        Agent1::_HP += 50;
    else if (_armour->GetSpecialTrait() == 2)
    {
        Agent1::_MovementSpeed += 3;
        Agent1::_FOV += 5;
    }
    else
    {
        Agent1::_gun->_Damage += 5;
        Agent1::_gun->_Critical_Strike_Chance += 10;
    }
}

Agent2::Agent2(char name, int x, int y, int hp, int fov, int ms)
    :Agents(name, x, y, hp, fov, ms)
{
    _gun = new Sniper();
    _armour = new BodyArmour_1();
    if (_armour->GetSpecialTrait() == 1)
        Agent2::_HP += 50;
    else if (_armour->GetSpecialTrait() == 2)
    {
        Agent2::_MovementSpeed += 3;
        Agent2::_FOV += 5;
    }
    else
    {
        Agent2::_gun->_Damage += 5;
        Agent2::_gun->_Critical_Strike_Chance += 10;
    }

}

Agent3::Agent3(char name, int x, int y, int hp, int fov, int ms)
    :Agents(name, x, y, hp, fov, ms)
{
    _gun = new Shotgun();
    _armour = new BodyArmour_2();
    if (_armour->GetSpecialTrait() == 1)
        Agent3::_HP += 50;
    else if (_armour->GetSpecialTrait() == 2)
    {
        Agent3::_MovementSpeed += 3;
        Agent3::_FOV += 5;
    }
    else
    {
        Agent3::_gun->_Damage += 5;
        Agent3::_gun->_Critical_Strike_Chance += 10;
    }
}

// daca incerc sa pun delete _gun delete _armour in Agent1/2/3 imi modifica jocul
// in sensul ca, fara sa modific altceva, jocul 2 va avea in loc de sniper, shotgun.
Agents::~Agents()
{
}
Agent1::~Agent1()
{
}
Agent2::~Agent2()
{
}
Agent3::~Agent3()
{
}

void Agents::Show_Stats() const
{
    std::cout<<"Name: "<<this->_Name<<"\n";
    std::cout<<"Current X && Current Y: "<<this->_CurrentX<<" && "<<this->_CurrentY<<"\n";
    std::cout<<"HP: "<<this->_HP<<"\n";
    std::cout<<"FOV: "<<this->_FOV<<"\n";
    std::cout<<"Movement speed: "<<this->_MovementSpeed<<"\n";
}

void Agent1::Show_Stats() const
{
    std::cout<<"Name: "<<this->_Name<<"\n";
    std::cout<<"Current X && Current Y: "<<this->_CurrentX<<" && "<<this->_CurrentY<<"\n";
    std::cout<<"HP: "<<this->_HP<<"\n";
    std::cout<<"FOV: "<<this->_FOV<<"\n";
    std::cout<<"Movement speed: "<<this->_MovementSpeed<<"\n";
    _armour->Show_BodyArmourStats();
    std::cout<<"\n";
    _gun->Show_GunStats();
    std::cout<<"\n";
}

void Agent2::Show_Stats() const
{
    std::cout<<"Name: "<<this->_Name<<"\n";
    std::cout<<"Current X && Current Y: "<<this->_CurrentX<<" && "<<this->_CurrentY<<"\n";
    std::cout<<"HP: "<<this->_HP<<"\n";
    std::cout<<"FOV: "<<this->_FOV<<"\n";
    std::cout<<"Movement speed: "<<this->_MovementSpeed<<"\n";
    _armour->Show_BodyArmourStats();
    std::cout<<"\n";
    _gun->Show_GunStats();
    std::cout<<"\n";
}

void Agent3::Show_Stats() const
{
    std::cout<<"Name: "<<this->_Name<<"\n";
    std::cout<<"Current X && Current Y: "<<this->_CurrentX<<" && "<<this->_CurrentY<<"\n";
    std::cout<<"HP: "<<this->_HP<<"\n";
    std::cout<<"FOV: "<<this->_FOV<<"\n";
    std::cout<<"Movement speed: "<<this->_MovementSpeed<<"\n";
    _armour->Show_BodyArmourStats();
    std::cout<<"\n";
    _gun->Show_GunStats();
    std::cout<<"\n";
}

bool Agents::isAlive()
{
    if (this->_HP>0)
        return true;
    return false;
}

bool Agent1::isAlive()
{
    if (Agent1::_HP>0)
        return true;
    return false;
}

bool Agent2::isAlive()
{
    if (Agent2::_HP>0)
        return true;
    return false;
}

bool Agent3::isAlive()
{
    if (Agent3::_HP>0)
        return true;
    return false;
}

Agents& Agents::operator - (const Agents& Aux)
{
    int dmg;
    if (this->_armour->_Armour >= 0)
        {
            dmg = this->_armour->_Armour - Aux._gun->_Damage;
            this->_armour->_Armour -= Aux._gun->_Damage;
            if (dmg < 0)
                this->_HP -= dmg;
        }
        else
        {
            this->_HP -= Aux._gun->_Damage;
        }
    return *this;
}

Agents& Agents::operator = (const Agents& Aux)
{
    this->_armour->_Armour = Aux._armour->_Armour;
    this->_armour->_Special_Trait = Aux._armour->_Special_Trait;
    this->_CurrentX = Aux._CurrentX;
    this->_CurrentY = Aux._CurrentY;
    this->_FOV = Aux._FOV;
    this->_gun = Aux._gun;
    this->_HP = Aux._HP;
    this->_MovementSpeed = Aux._MovementSpeed;
    this->_Name = Aux._Name;
    return *this;
}
