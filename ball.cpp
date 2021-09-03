#include "stdlib.h"
#include <iostream>
#include "ball.h"

Ball::Ball(int posX, int posY)
    : x(posX), y(posY), originalX(posX), originalY(posY), dir(STOP) {}

void Ball::Reset()
{
    x = originalX;
    y = originalY;
    dir = STOP;
}

void Ball::ChangeDirRand()
{
    dir = (Direction)(rand() % 6 + 1);
}

void Ball::ChangeDir(Direction newDir)
{
    dir = newDir;
}

void Ball::Move()
{
    switch (dir)
    {
    case STOP:
        break;
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UPLEFT:
        x--;
        y--;
        break;
    case DOWNLEFT:
        x--;
        y++;
        break;
    case UPRIGHT:
        x++;
        y--;
        break;
    case DOWNRIGHT:
        x++;
        y++;
        break;
    default:
        break;
    }
}
std::ostream &operator<<(std::ostream &o, Ball b)
{
    o << "Ball [" << b.x << "," << b.y << "][" << b.dir << "]";
    return o;
}

/*
int main()
{
    Ball b(0, 0);
    std::cout << b << std::endl;
    b.ChangeDir(DOWNRIGHT);
    std::cout << b << std::endl;
    b.Move();
    std::cout << b << std::endl;
    b.ChangeDirRand();
    b.Move();
    std::cout << b << std::endl;
    b.ChangeDirRand();
    b.ChangeDirRand();
    b.Move();
    std::cout << b << std::endl;
}
*/