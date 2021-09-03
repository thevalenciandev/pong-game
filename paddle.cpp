#include <iostream>

class Paddle
{
private:
    int x, y;
    int originalX, originalY;
public:
    Paddle(int posX, int posY)
        : x(posX), y(posY), originalX(posX), originalY(posY) {}
    void Reset()
    {
        x = originalX;
        y = originalY;
    }
    void MoveUp() { y--; }
    void MoveDown() { y++; }
    friend std::ostream& operator<<(std::ostream &o, Paddle b)
    {
        o << "Paddle [" << b.x << "," << b.y << "]";
        return o;
    }
};


int main()
{
    Paddle p1(0, 0);
    Paddle p2(10, 0);
    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;
    p1.MoveUp();
    p2.MoveDown();
    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;
}