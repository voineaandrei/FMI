#include "Map.h"

Map::Map()
{
    this -> _M = new char* [33];
    for (int i = 0; i < 33; i++)
    this -> _M[i] = new char [33];
    for (int i = 0; i < 33; i++)
    memset (_M[i], '_', 33  * sizeof(char));
}

Map::~Map()
{
    for (int i = 0; i < 33; i++)
        delete[] _M[i];
    delete[] _M;
}

void Map::Map_Show()
{
    int i, j;
    std::cout<<"  ";
    for (i = 0; i < 33; i++)
        std::cout<<i%10<<" ";
    std::cout<<std::endl;
    for (i = 0; i < 33; i++)
    {
        std::cout<<i%10<<" ";
        for (j = 0; j < 33; j++)
            std::cout<<_M[i][j]<<" ";
        std::cout<<std::endl;
    }
}

void Map::Update(int i, int j, char c)
{
    _M[i][j]=c;
}
