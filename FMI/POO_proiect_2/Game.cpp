#include "Game.h"

Game::Game()
    :_Harta(Map())
    ,_A(Agent1('A'))
    ,_B(Agent2('B'))
    ,_C(Agent3('C'))
{
    _Harta.Update(_A._CurrentX, _A._CurrentY, _A._Name);
    while (_B._CurrentX == _A._CurrentX && _B._CurrentY == _A._CurrentY)
        _B = Agent2();
    _Harta.Update(_B._CurrentX, _B._CurrentY, _B._Name);
    while (_C._CurrentX == _A._CurrentX && _C._CurrentY == _A._CurrentY || _C._CurrentX == _B._CurrentX && _C._CurrentY == _B._CurrentY)
        _C = Agent3();
    _Harta.Update(_C._CurrentX, _C._CurrentY, _C._Name);
}

int Game::inRange(Agents Aux, int **Coord) // se verifica matricea in jurul player-ului de la i-ul si j-ul curent +,- fov
{                                          // si prin referinta se pastreaza un vector cu coord[par]=i si coord[impar]=j
    int i, j, k = 0;
    for (i=0; i<4; i++)
        (*Coord)[i] = -100;
    int mini, minj, maxi, maxj;
    mini = Aux._CurrentX - Aux._FOV;
    maxi = Aux._CurrentX + Aux._FOV;
    minj = Aux._CurrentY - Aux._FOV;
    maxj = Aux._CurrentY + Aux._FOV;
    if (mini < 0)
        mini = 0;
    if (maxi > 32)
        maxi = 32;
    if (minj < 0)
        minj = 0;
    if (maxj > 32)
        maxj = 32;
    for (i = mini; i <= maxi; i++)
        for (j = minj; j <= maxj; j++)
            if (_Harta._M[i][j] != '_' && _Harta._M[i][j] != Aux._Name)
            {
                (*Coord)[k++] = i;
                (*Coord)[k++] = j;
            }
    return k;
}

void Game::isTargeting(Agents* Aux, Agents** ptrAgent) // se verifica daca sunt jucatori in range-ul armei
{
    int mini, minj, maxi, maxj;
    int i, j;
    bool OK = false;
    mini = (*Aux)._CurrentX - (*Aux)._gun->_Effective_Range;
    maxi = (*Aux)._CurrentX + (*Aux)._gun->_Effective_Range;
    minj = (*Aux)._CurrentY - (*Aux)._gun->_Effective_Range;
    maxj = (*Aux)._CurrentY + (*Aux)._gun->_Effective_Range;
    if (mini < 0)
        mini = 0;
    if (maxi > 32)
        maxi = 32;
    if (minj < 0)
        minj = 0;
    if (maxj > 32)
        maxj = 32;
    for (i = mini; i <= maxi && OK == false; i++)
        for (j = minj; j <= maxj && OK == false; j++)
            if (_Harta._M[i][j] != '_' && _Harta._M[i][j] != (*Aux)._Name)
                OK = true;
    if ( OK == true )                   // daca da, atunci va trage dupa el
    {
        srand(time(NULL));
        int RNG_Acc, RNG_CSC;
        for (i = 0; i < (*Aux)._gun->_Fire_Rate; i++)
        {
            RNG_Acc = rand() % 100;
            if (RNG_Acc < (*Aux)._gun->_Accuracy)
            {
                RNG_CSC = rand() % 100;
                if (RNG_CSC < (*Aux)._gun->_Critical_Strike_Chance)
                {
                    std::cout<<"HEADSHOT!!! ";
                    std::cout<<(*Aux)._Name<<" hit "<<(**ptrAgent)._Name<<" for "<<(*Aux)._gun->_Damage*2<<"\n";
                    if ((**ptrAgent)._armour->_Armour > 0)
                    {
                        (**ptrAgent)._armour->_Armour -= (*Aux)._gun->_Damage*2;
                        (*Aux)._gun->_Mag--;
                        if ((**ptrAgent)._armour->_Armour < 0)
                            (**ptrAgent)._HP -= (-1)*((**ptrAgent)._armour->_Armour);
                    }
                    else
                    {
                        (**ptrAgent)._HP -= (*Aux)._gun->_Damage*2;
                        (*Aux)._gun->_Mag--;
                    }
                }
                else
                {
                    std::cout<<(*Aux)._Name<<" hit "<<(**ptrAgent)._Name<<" for "<<(*Aux)._gun->_Damage<<"\n";
                    if ((**ptrAgent)._armour->_Armour > 0)
                    {
                        (**ptrAgent)._armour->_Armour -= (*Aux)._gun->_Damage;
                        (*Aux)._gun->_Mag--;
                        if ((**ptrAgent)._armour->_Armour < 0)
                            (**ptrAgent)._HP -= (-1)*((**ptrAgent)._armour->_Armour);
                    }
                    else
                    {
                        (**ptrAgent)._HP -= (*Aux)._gun->_Damage;
                        (*Aux)._gun->_Mag--;
                    }
                }
            }
            else
            {
                std::cout<<(*Aux)._Name<<" MISSES!!! :(\n";
                (*Aux)._gun->_Mag--;
            }
        }
        if ((**ptrAgent)._HP <= 0)
        {
            _Harta.Update((**ptrAgent)._CurrentX, (**ptrAgent)._CurrentY, '_');
            (**ptrAgent)._CurrentX = (**ptrAgent)._CurrentY = 100;
        }
    }
    else     // DACA NU, va merge spre el, cu conditia ca 2 playeri nu pot sta pe aceeasi pozitie
    {
        int MS = (*Aux)._MovementSpeed;
        _Harta.Update((*Aux)._CurrentX, (*Aux)._CurrentY, '_');
        if ((**ptrAgent)._CurrentX <= (*Aux)._CurrentX)
        {
            if ((**ptrAgent)._CurrentY < (*Aux)._CurrentY)
            {
                while (MS > 0 && ((**ptrAgent)._CurrentY != (*Aux)._CurrentY) && (**ptrAgent)._CurrentX != (*Aux)._CurrentX)
                {
                    if ((*Aux)._CurrentX != (**ptrAgent)._CurrentX + 1 || (*Aux)._CurrentY != (**ptrAgent)._CurrentY + 1)
                    {
                        (*Aux)._CurrentY--;
                        (*Aux)._CurrentX--;
                        MS--;
                    }
                    else
                    {
                        MS=0;
                    }
                }
                while (MS > 0 && (**ptrAgent)._CurrentY == (*Aux)._CurrentY && (*Aux)._CurrentX != (**ptrAgent)._CurrentX + 1)
                {
                    (*Aux)._CurrentX--;
                    MS--;
                }
                while (MS > 0 && (**ptrAgent)._CurrentX == (*Aux)._CurrentX && (*Aux)._CurrentY != (**ptrAgent)._CurrentY + 1)
                {
                    (*Aux)._CurrentY--;
                    MS--;
                }
            }
            else
            {
                while (MS > 0 && ((**ptrAgent)._CurrentY != (*Aux)._CurrentY) && (**ptrAgent)._CurrentX != (*Aux)._CurrentX)
                {
                    if ((*Aux)._CurrentX != (**ptrAgent)._CurrentX + 1 || (*Aux)._CurrentY != (**ptrAgent)._CurrentY - 1)
                    {
                        (*Aux)._CurrentY++;
                        (*Aux)._CurrentX--;
                        MS--;
                    }
                    else
                    {
                        MS=0;
                    }
                }
                while (MS > 0 && ((**ptrAgent)._CurrentY == (*Aux)._CurrentY) && (*Aux)._CurrentX != (**ptrAgent)._CurrentX + 1)
                {
                    (*Aux)._CurrentX--;
                    MS--;
                }
                while (MS > 0 && ((**ptrAgent)._CurrentX == (*Aux)._CurrentX) && (*Aux)._CurrentY != (**ptrAgent)._CurrentY - 1)
                {
                    (*Aux)._CurrentY++;
                    MS--;
                }
            }
        }
        else
        {
            if ((**ptrAgent)._CurrentY < (*Aux)._CurrentY)
            {
                while (MS > 0 && ((**ptrAgent)._CurrentY != (*Aux)._CurrentY) && (**ptrAgent)._CurrentX != (*Aux)._CurrentX)
                {
                    if((*Aux)._CurrentX != (**ptrAgent)._CurrentX - 1 || (*Aux)._CurrentY != (**ptrAgent)._CurrentY + 1)
                    {
                        (*Aux)._CurrentY--;
                        (*Aux)._CurrentX++;
                        MS--;
                    }
                    else
                    {
                        MS=0;
                    }
                }
                while (MS > 0 && ((**ptrAgent)._CurrentY == (*Aux)._CurrentY) && (*Aux)._CurrentX != (**ptrAgent)._CurrentX - 1)
                {
                    (*Aux)._CurrentX++;
                    MS--;
                }
                while (MS > 0 && ((**ptrAgent)._CurrentX == (*Aux)._CurrentX) && (*Aux)._CurrentY != (**ptrAgent)._CurrentY + 1)
                {
                    (*Aux)._CurrentY--;
                    MS--;
                }
            }
            else
            {
                while (MS > 0 && ((**ptrAgent)._CurrentY != (*Aux)._CurrentY) && (**ptrAgent)._CurrentX != (*Aux)._CurrentX)
                {
                    if((*Aux)._CurrentY != (**ptrAgent)._CurrentY - 1 || (*Aux)._CurrentX != (**ptrAgent)._CurrentX - 1)
                    {
                        (*Aux)._CurrentY++;
                        (*Aux)._CurrentX++;
                        MS--;
                    }
                    else
                    {
                        MS=0;
                    }
                }
                while (MS > 0 && ((**ptrAgent)._CurrentY == (*Aux)._CurrentY) && (*Aux)._CurrentX != (**ptrAgent)._CurrentX - 1)
                {
                    (*Aux)._CurrentX++;
                    MS--;
                }
                while (MS > 0 && ((**ptrAgent)._CurrentX == (*Aux)._CurrentX) && (*Aux)._CurrentY != (**ptrAgent)._CurrentY - 1)
                {
                    (*Aux)._CurrentY++;
                    MS--;
                }
            }
        }
        _Harta.Update((*Aux)._CurrentX, (*Aux)._CurrentY, (*Aux)._Name);
    }
}

void Game::isMoving(Agents* Aux)  // jucatorul se muta spre mijlocul tablei
{
    _Harta.Update((*Aux)._CurrentX, (*Aux)._CurrentY, '_');
    int x = (*Aux)._CurrentX - 16;
    int y = (*Aux)._CurrentY - 16;
    int ms = (*Aux)._MovementSpeed;
    if ( x <= 0 )
    {
        if ( y <= 0)
        {
            while (ms != 1)
            {
                (*Aux)._CurrentX++;
                (*Aux)._CurrentY++;
                ms--;
            }
            if (_Harta._M[(*Aux)._CurrentX + 1][(*Aux)._CurrentY + 1] == '_')
            {
                (*Aux)._CurrentX++;
                (*Aux)._CurrentY++;
            }
        }
        else
        {
            while (ms != 0)
            {
                (*Aux)._CurrentX++;
                (*Aux)._CurrentY--;
                ms--;
            }
            if (_Harta._M[(*Aux)._CurrentX + 1][(*Aux)._CurrentY - 1] == '_')
            {
                (*Aux)._CurrentX++;
                (*Aux)._CurrentY--;
            }
        }
    }
    else
    {
        if (y <= 0)
        {
            while (ms != 0)
            {
                (*Aux)._CurrentX--;
                (*Aux)._CurrentY++;
                ms--;
            }
            if (_Harta._M[(*Aux)._CurrentX - 1][(*Aux)._CurrentY + 1] == '_')
            {
                (*Aux)._CurrentX--;
                (*Aux)._CurrentY++;
            }
        }
        else
        {
            while (ms != 0)
            {
                (*Aux)._CurrentX--;
                (*Aux)._CurrentY--;
                ms--;
            }
            if (_Harta._M[(*Aux)._CurrentX - 1][(*Aux)._CurrentY - 1] == '_')
            {
                (*Aux)._CurrentX--;
                (*Aux)._CurrentY--;
            }
        }
    }
    _Harta.Update((*Aux)._CurrentX, (*Aux)._CurrentY, (*Aux)._Name);
}

void Game::Turn(Agents* _AUX) // Tura unui jucator
{
    if ((*_AUX)._gun->_Mag == 0)   // daca nu mai are gloante in magazie, acesta trebuie sa incarce, ceea ce ii ia runda
    {
        if ((*_AUX)._gun->_ReloadATM != (*_AUX)._gun->_Reload_Time)
        {
            (*_AUX)._gun->_ReloadATM++;
            cout<<(*_AUX)._Name<<" RELOADING!!!"<<endl;
            return;
        }
        else
        {
            (*_AUX)._gun->_ReloadATM = 0;
            (*_AUX)._gun->_Mag = (*_AUX)._gun->_Mag_Size;
        }
    }
    int i;
    int *Coord = new int [4];
    int coord1, coord2;
    int Nr_Coordonate;
    Agents *ptr = NULL;
    Nr_Coordonate = inRange((*_AUX), &Coord);   // Se verifica cine e in range-ul FOV-ului respectivului player
    if (Nr_Coordonate == 0)  // Daca nu e nimeni, se muta in mijlocul mapei, fara sa poate sa se aseze pe alt jucator
        isMoving(&(*_AUX));
    else  // Daca vede o persoana sau 2, va calcula care e mai aproape si va merge spre el, desi algoritmul folosit nu este testat
    {
        coord1 = abs((*_AUX)._CurrentX - Coord[0]) + abs((*_AUX)._CurrentY - Coord[1]); // nu stiu cat de corect este calculul
        coord2 = abs((*_AUX)._CurrentX - Coord[2]) + abs((*_AUX)._CurrentY - Coord[3]); // dar ideea e sa mearga spre cineva
        if (coord1 < coord2)
        {
            if (_A._CurrentX == Coord[0] && _A._CurrentY == Coord[1])
                ptr = &_A;
            if (_B._CurrentX == Coord[0] && _B._CurrentY == Coord[1])
                ptr = &_B;
            if (_C._CurrentX == Coord[0] && _C._CurrentY == Coord[1])
                ptr = &_C;
        }
        else
        {
            if (_A._CurrentX == Coord[2] && _A._CurrentY == Coord[3])
                ptr = &_A;
            if (_B._CurrentX == Coord[2] && _B._CurrentY == Coord[3])
                ptr = &_B;
            if (_C._CurrentX == Coord[2] && _C._CurrentY == Coord[3])
                ptr = &_C;
        }
        isTargeting(&(*_AUX), &ptr); // da target pe pers resp
    }
}

int Game::Simulate_Round()  // desfasurarea unei runde
{
    if (_A.isAlive()) // daca e in viata
        if (_B.isAlive() || _C.isAlive()) // si cel putin alt player este in viata
        {
            Turn(&_A); // atunci isi va face mutarea
        }
        else
        {
            std::cout<<"A CASTIGAT "<<_A._Name<<"!!!!"; // daca nu, a castigat si se incheie jocul
            return 0;
        }
    if (_B.isAlive())
        if(_A.isAlive() || _C.isAlive())
        {
            Turn(&_B);
        }
        else
        {
            std::cout<<"A CASTIGAT "<<_B._Name<<"!!!!";
            return 0;
        }
    if (_C.isAlive())
        if (_A.isAlive() || _B.isAlive())
        {
            Turn(&_C);
        }
        else
        {
            std::cout<<"A CASTIGAT "<<_C._Name<<"!!!!";
            return 0;
        }
    return 1;
}
void Game::Show_Round()
{
    _Harta.Map_Show();
    _A.Show_Stats();
    _B.Show_Stats();
    _C.Show_Stats();
}
void Game::Show_Map()
{
    _Harta.Map_Show();
}
void Game::Show_TotalHPRemaining() const
{
    std::cout<<_A._Name<<":\nHP: "<<_A._HP<<"\nArmour: "<<_A._armour->_Armour<<"\n";
    std::cout<<_B._Name<<":\nHP: "<<_B._HP<<"\nArmour: "<<_B._armour->_Armour<<"\n";
    std::cout<<_C._Name<<":\nHP: "<<_C._HP<<"\nArmour: "<<_C._armour->_Armour<<"\n";
}
