#pragma once
#include <iostream>

enum Direction
{
    STOP = 0,
    LEFT = 1,
    UPLEFT = 2,
    DOWNLEFT = 3,
    RIGHT = 4,
    UPRIGHT = 5,
    DOWNRIGHT = 6
};

class Ball
{
public:
    Ball(int posX, int posY);
    int GetX();
    int GetY();
    void Reset();
    void ChangeDirRand();
    void ChangeDir(Direction newDir);
    void Move();
    friend std::ostream &operator<<(std::ostream &o, Ball b);

private:
    int x, y;
    int originalX, originalY;
    Direction dir;
};