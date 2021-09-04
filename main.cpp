#include "curses.h"
#include "paddle.h"
#include "ball.h"
#include "time.h"

class Game
{
private:
    int width, height;
    int score1, score2;
    int throttle; // Used to improve input responsiveness (in other words, to solve players lag when holding key down)
    char up1, down1, up2, down2;
    bool quit;
    Ball *ball;
    Paddle *player1;
    Paddle *player2;
    void Input()
    { 
        if (throttle++ == 3)
        {
            // Move ball only every 3 times we enter this loop. This makes sure the ball doesn't go to fast
            // as we reduce the napms (which allows the players movement to be more responsive to user input)
            ball->Move();
            throttle = 0;
        }

        int current = getch();
        if (current == 'b')
        {
            quit = true;
            return;
        }

        if (current == up1 && player1->GetY() > 0)
            player1->MoveUp();
        else if (current == up2 && player2->GetY() > 0)
            player2->MoveUp();
        else if (current == down1 && player1->GetY() + 4 < height)
            player1->MoveDown();
        else if (current == down2 && player2->GetY() + 4 < height)
            player2->MoveDown();

        if (ball->GetDirection() == STOP)
            ball->ChangeDirRand();
    }
    void Draw()
    {
        move(0, 0); // move cursor to top left so we can redraw over the previous screen.

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
                int player1x = player1->GetX();
                int player1y = player1->GetY();
                int player2x = player2->GetX();
                int player2y = player2->GetY();
                if (j == ballx && i == bally)
                    addch('O');
                else if (j == player1x && (i == player1y || i == player1y + 1 || i == player1y + 2 || i == player1y + 3))
                    addch('\xDB');
                else if (j == player2x && (i == player2y || i == player2y + 1 || i == player2y + 2 || i == player2y + 3))
                    addch('\xDB');
                else
                    addch(' ');
            }
            addch('\n'); // finish that row
        }

        // Draw bottom wall
        for (int i = 0; i < width; i++)
            addch('\xB2');
        addch('\n');
        printw("Score player 1: %d\n", score1);
        printw("Score player 2: %d\n", score2);

        napms(15);
        refresh(); // Draw.
    }

    void Logic()
    {
        int ballx = ball->GetX();
        int bally = ball->GetY();
        Direction balldir = ball->GetDirection();
        int player1x = player1->GetX();
        int player1y = player1->GetY();
        int player2x = player2->GetX();
        int player2y = player2->GetY();
        // If any of the 4 parts of the left paddle (player1) hits the ball
        for (int i = 0; i < 4; i++)
            if (ballx == player1x + 1 && bally == player1y + i)
                ball->ChangeDir((Direction)(rand() % 3 + 4)); // randomise among 4,5,6

        // If any of the 4 parts of the right paddle (player2) hits the ball
        for (int i = 0; i < 4; i++)
            if (ballx == player2x - 1 && bally == player2y + i)
                ball->ChangeDir((Direction)(rand() % 3 + 1)); // randomise among 1,2,3

        if (ballx == 1) // left wall
            ScoreUp(player2);
        else if (ballx == width - 1) // right wall
            ScoreUp(player1);
        else if (bally == 0 && balldir == UPRIGHT) // top wall
            ball->ChangeDir(DOWNRIGHT);
        else if (bally == 0 && balldir == UPLEFT) // top wall
            ball->ChangeDir(DOWNLEFT);
        else if (bally == height - 1 && balldir == DOWNRIGHT) // bottom wall
            ball->ChangeDir(UPRIGHT);
        else if (bally == height - 1 && balldir == DOWNLEFT) // bottom wall
            ball->ChangeDir(UPLEFT);
    }

public:
    Game(int width, int height)
        : width(width), height(height), score1(0), score2(0), throttle(0), up1('x'), down1('z'), up2('k'), down2('j'), quit(false),
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
    Game game(90, 45);
    game.Run();
}
