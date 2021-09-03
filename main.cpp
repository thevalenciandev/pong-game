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
        clear(); // Clear screen.

        // Draw top wall
        for (int i = 0; i < width; i++)
            addch('\xB2');
        addch('\n');

        for (int i = 0; i < height; i++) // y
        {
            for (int j = 0; j < width; j++) // x
            {
                if (j == 0 || j == width - 1)
                {
                    addch('\xB2'); // Draw lateral walls
                    continue;
                }
                int ballx = ball->GetX();
                int bally = ball->GetY();
                if (j == ballx && i == bally)
                {
                    addch('O');
                    continue;
                }
                int player1x = player1->GetX();
                int player1y = player1->GetY();
                if (j == player1x && i == player1y)
                {
                    addch('\xDB');
                    continue;
                }
                int player2x = player2->GetX();
                int player2y = player2->GetY();
                if (j == player2x && i == player2y)
                {
                    addch('\xDB');
                    continue;
                }
                addch(' ');
            }
            addch('\n'); // finish that row
        }

        // Draw bottom wall
        for (int i = 0; i < width; i++)
            addch('\xB2');
        addch('\n');

        refresh(); // Draw.
        napms(100);
    }
    void Logic()
    {
    }

public:
    Game(int width, int height)
        : width(width), height(height), score1(0), score2(0), up1('w'), down1('s'), up2('i'), down2('k'), quit(false),
          ball(new Ball(width / 2, height / 2)),
          player1(new Paddle(2, height / 2 - 3)),
          player2(new Paddle(width - 3, height / 2 - 3))
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
        endwin(); // Stop ncurses.
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
