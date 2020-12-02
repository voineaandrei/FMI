#include "Gun.h"

// dmg = Damage => Valoare cu care scade HP-ul / Armura inamicului odata ce este lovit
// mag = Mag Size => Cate gloante per cartus are arma
//       Mag => Valoarea ce tine cont cate gloante are jucatorul in real-time
// FR = Fire Rate => Cate gloante trage pe runda
// ER = Effective Range => La ce distanta ajunge glontul
// RT = Reload Time => Dupa ce ramane fara gloante, trebuie sa stea *RT* runde ca sa reincarce
// acc = Accuracy => Sansa de a nimeri
// CSC = Critical Strike Chance => Sansa de a da double damage

Gun::Gun(string nume, int dmg, int mag, int FR, int ER, int RT, int acc, int CSC)
    :_Name(nume)
    ,_Damage(dmg)
    ,_Mag_Size(mag)
    ,_Mag(mag)
    ,_Fire_Rate(FR)
    ,_Effective_Range(ER)
    ,_Reload_Time(RT)
    ,_Accuracy(acc)
    ,_Critical_Strike_Chance(CSC)
    ,_ReloadATM(0)
{
}

Assault_Rifle::Assault_Rifle(string nume, int dmg, int mag, int FR, int ER, int RT, int acc, int CSC)
    :Gun(nume, dmg, mag, FR, ER, RT, acc, CSC)
{
}

Sniper::Sniper(string nume, int dmg, int mag, int FR, int ER, int RT, int acc, int CSC)
    :Gun(nume, dmg, mag, FR, ER, RT, acc, CSC)
{
}

Shotgun::Shotgun(string nume, int dmg, int mag, int FR, int ER, int RT, int acc, int CSC)
    :Gun(nume, dmg, mag, FR, ER, RT, acc, CSC)
{
}

void Gun::Show_GunStats() const
{
    std::cout<<"Gun: "<<this->_Name<<"\n";
    std::cout<<"Damage: "<<this->_Damage<<"\n";
    std::cout<<"Mag Size: "<<this->_Mag_Size<<"\n";
    std::cout<<"Fire Rate: "<<this->_Fire_Rate<<"\n";
    std::cout<<"Effective Range: "<<this->_Effective_Range<<"\n";
    std::cout<<"Reload Time: "<<this->_Reload_Time<<"\n";
    std::cout<<"Accuracy: "<<this->_Accuracy<<"%\n";
    std::cout<<"Critical Strike Chance: "<<this->_Critical_Strike_Chance<<"%\n";
}

void Assault_Rifle::Show_GunStats() const
{
    std::cout<<"Gun: "<<this->_Name<<"\n";
    std::cout<<"Damage: "<<this->_Damage<<"\n";
    std::cout<<"Mag Size: "<<this->_Mag_Size<<"\n";
    std::cout<<"Fire Rate: "<<this->_Fire_Rate<<"\n";
    std::cout<<"Effective Range: "<<this->_Effective_Range<<"\n";
    std::cout<<"Reload Time: "<<this->_Reload_Time<<"\n";
    std::cout<<"Accuracy: "<<this->_Accuracy<<"%\n";
    std::cout<<"Critical Strike Chance: "<<this->_Critical_Strike_Chance<<"%\n";
}

void Sniper::Show_GunStats() const
{
    std::cout<<"Gun: "<<this->_Name<<"\n";
    std::cout<<"Damage: "<<this->_Damage<<"\n";
    std::cout<<"Mag Size: "<<this->_Mag_Size<<"\n";
    std::cout<<"Fire Rate: "<<this->_Fire_Rate<<"\n";
    std::cout<<"Effective Range: "<<this->_Effective_Range<<"\n";
    std::cout<<"Reload Time: "<<this->_Reload_Time<<"\n";
    std::cout<<"Accuracy: "<<this->_Accuracy<<"%\n";
    std::cout<<"Critical Strike Chance: "<<this->_Critical_Strike_Chance<<"%\n";
}

void Shotgun::Show_GunStats() const
{
    std::cout<<"Gun: "<<this->_Name<<"\n";
    std::cout<<"Damage: "<<this->_Damage<<"\n";
    std::cout<<"Mag Size: "<<this->_Mag_Size<<"\n";
    std::cout<<"Fire Rate: "<<this->_Fire_Rate<<"\n";
    std::cout<<"Effective Range: "<<this->_Effective_Range<<"\n";
    std::cout<<"Reload Time: "<<this->_Reload_Time<<"\n";
    std::cout<<"Accuracy: "<<this->_Accuracy<<"%\n";
    std::cout<<"Critical Strike Chance: "<<this->_Critical_Strike_Chance<<"%\n";
}


Gun::~Gun() {}
Assault_Rifle::~Assault_Rifle() {}
Sniper::~Sniper() {}
Shotgun::~Shotgun() {}

