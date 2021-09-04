# pong-game
Simple console-based "Pong" game, using ncurses.

![image](https://user-images.githubusercontent.com/45404603/132106448-846f353d-22eb-4066-8d1a-749c225bef50.png)

This is heavily based on Nvitanovic's implementation, though with a few key differences/improvements:
- No flickering of the screen
- No input lag
- Separate files for ball and paddle definitions and implementations
- Usage of ncurses (instead of conio)

1) Build command (replace /mnt/c/Dev/ by your directory):

`
/usr/bin/g++ -g /mnt/c/Dev/pong-game/main.cpp /mnt/c/Dev/pong-game/ball.cpp /mnt/c/Dev/pong-game/paddle.cpp -o /mnt/c/Dev/pong-game/main -lncursesw
`

2) Execute:

`./main`
