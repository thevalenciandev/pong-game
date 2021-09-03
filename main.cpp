#include "curses.h"
#include "paddle.h"
#include "ball.h"
#include "time.h"

class Game
{
private:
    int width, height;
    int score1, score2;
    char up1, down1, up2, down2;
    bool quit;
    Ball *ball;
    Paddle *player1;
    Paddle *player2;
    void Input()
    {
    }
    void Draw()
    {
        clear();
        // Draw walls
        for (int i = 0; i < width + 2; i++)
            addch('#');
        addch('\n');
        refresh();
    }
    void Logic()
    {
    }

public:
    Game(int width, int heigth)
        : width(width), height(height), score1(0), score2(0), up1('w'), down1('s'), up2('i'), down2('k'), quit(false),
          ball(new Ball(width / 2, height / 2)),
          player1(new Paddle(1, height / 2 - 3)),
          player2(new Paddle(width - 2, height / 2 - 3))
    {
        srand(time(NULL)); // seed our random numbers
        InitGraphics();
    }
    void InitGraphics()
    {
        // Using ncurses lib.
        initscr();            // init curses mode (allocs mem for present window, stdscr)
        noecho();             // inputs by user will not be displayed on screen
        cbreak();             // read character without having to press ENTER (disable line buffering)
        keypad(stdscr, TRUE); // enable arrow keys
        scrollok(stdscr, TRUE);
        nodelay(stdscr, TRUE); // non-blocking getchar for user input
        start_color();
        init_pair(1, COLOR_CYAN, COLOR_BLACK);
    }
    ~Game()
    {
        delete ball, player1, player2;
    }
    void ScoreUp(Paddle *player)
    {
        if (player == player1)
            score1++;
        else if (player == player2)
            score2++;

        ball->Reset();
        player1->Reset();
        player2->Reset();
    }

    void Run()
    {
        while (!quit)
        {
            Input();
            Draw();
            Logic();
        }
    }
};

int main()
{
    Game game(100, 50);
    game.Run();
}
