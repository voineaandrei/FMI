#ifndef MAP_H
#define MAP_H
#include <stdio.h>
#include <iostream>
#include <string.h>

class Map
{
    public:
        Map();
        ~Map();
        void Map_Show();
        void Update(int i, int j, char c);

        friend class Game;
    private:
        char** _M;

};

#endif // MAP_H
