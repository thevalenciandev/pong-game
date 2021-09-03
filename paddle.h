#pragma once
#include <iostream>

class Paddle
{
public:
    Paddle(int posX, int posY);
    void Reset();
    void MoveUp();
    void MoveDown();
    friend std::ostream &operator<<(std::ostream &o, Paddle b);

private:
    int x, y;
    int originalX, originalY;
};