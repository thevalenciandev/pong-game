#include "stdlib.h"
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
private:
    int x, y;
    int originalX, originalY;
    Direction dir;

public:
    Ball(int posX, int posY)
        : x(posX), y(posY), originalX(posX), originalY(posY), dir(STOP) {}

    void Reset()
    {
        x = originalX;
        y = originalY;
        dir = STOP;
    }

    void ChangeDirRand()
    {
        dir = (Direction)(rand() % 6 + 1);
    }

    void ChangeDir(Direction newDir)
    {
        dir = newDir;
    }

    void Move()
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
    friend std::ostream& operator<<(std::ostream &o, Ball b)
    {
        o << "Ball [" << b.x << "," << b.y << "][" << b.dir << "]";
        return o;
    }
};

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