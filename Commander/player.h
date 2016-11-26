#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <random>
#include <ctime>
#include <iostream>
#include "cell.h"
using namespace std;

class Player
{
    vector<vector<Cell>> table;
    bool isEmpty(vector<int> array)
    {
        for(unsigned i = 0; i < array.size(); i++)
            if(array[i] != 0)
                return false;
        return true;
    }
    void generateShips()
    {
        vector<vector<bool>> visited(SIZE, vector<bool>(SIZE, false));
        pair<int, int> pos;
        for(unsigned i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4 - i; j++)
            {
                bool isVertical = rand() % 2;
                if(i < 2)
                {
                    do
                    {
                        pos.first = rand() % SIZE;
                        pos.second = rand() % SIZE;
                    }
                    while(!visited[pos.first][pos.second]);
                    if(i == 1)
                    {
                        bool placed = false;
                        if(isVertical)
                        {
                            if(pos.second + 1 != SIZE)
                            {
                                if(!visited[pos.first][pos.second + 1])
                                {
                                    for(int k = -1; k < 2; k++)
                                    {
                                        for(int j = -1; j < 3; j++)
                                        {
                                            if((pos.first + k >= 0) && (pos.first + k < SIZE) &&
                                            (pos.second + j >= 0) && (pos.second + j < SIZE))
                                            {
                                                visited[pos.first + k][pos.second + j] == 0;
                                            }
                                        }
                                    }
                                    placed = true;
                                }
                            }
                            if(!placed)
                            {
                                if(pos.second - 1 >= 0)
                                {
                                    if(!visited[pos.first][pos.second - 1])
                                    {
                                        for(int k = -1; k < 2; k++)
                                        {
                                            for(int j = -2; j < 2; j++)
                                            {
                                                if((pos.first + k >= 0) && (pos.first + k < SIZE) &&
                                                (pos.second + j >= 0) && (pos.second + j < SIZE))
                                                {
                                                    visited[pos.first + k][pos.second + j] == 0;
                                                }
                                            }
                                        }
                                        placed = true;
                                    }
                                }
                                else
                                    j--;
                            }
                        }
                    }
                }
                else
                {
                    pos.first = rand() % SIZE;
                    pos.second = rand() % SIZE;
                    bool placed = true;
                    if(isVertical)
                    {
                        for(int k = 0; k < 4; i++)
                        {
                            if((pos.second - 3 + k >= 0) && (pos.second - k < SIZE))
                            {
                                for(int j = -3 + k; j <= k; j++)
                                {
                                    if(visited[pos.first][pos.second + f])
                                    {
                                        placed = false;
                                        j = k;
                                    }
                                }
                            }
                            if(placed)
                            {
                                for(t = -1; t < 2; t++)
                                    for(int j = -4 + k; j <= k + 1; j++)
                                    {
                                        if((pos.first + t >= 0) && (pos.first + t < SIZE) &&
                                                (pos.second + j >= 0) && (pos.second + j < SIZE))
                                            visited[pos.first + t][pos.second + j] = true;
                                    }
                                k = 4;
                            }
                        }
                    }
                    else
                    {
                        for(int k = 0; k < 4; k++)
                        {
                            if((pos.first - 3 + k >= 0) && (pos.first + k < SIZE))
                            {
                                placed = true;
                                for(unsigned j = -3 + k; j <= k; j++)
                                {
                                    if(visited[pos.first + j][pos.second])
                                    {
                                        placed = false;
                                        j = k;
                                    }
                                }
                                if(placed)
                                {

                                }
                            }
                        }
                    }
                }
            }
        }
    }

public:
    Player() { srand(time(nullptr)); generateShips(); }
    void show() {}
};

#endif // PLAYER_H
