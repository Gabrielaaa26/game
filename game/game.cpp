#include<conio.h>
#include<string>
#include<windows.h>
#include<iostream>

using std::cin;
using std::cout;
struct  Obiect
{
    int x;
    int y;
};
enum Directii
{
    STOP,
    left,
    right,
    down,
    up,
};
bool GameOver;
int height;
int width;
Obiect snake;
Obiect point;
Obiect tail[200];
int ntail = 0;
Directii dir;
int scor = 0;


void Setup()
{
    GameOver = false;
    height = 15;
    width = 30;
    snake.x = 5;
    snake.y = 5;
    point.x = rand() % width;
    point.y = rand() % height;
    dir = STOP;
}

void Draw()
{
    system("cls");
    for (int i = 0;i < width;i++) cout << "#";
    cout << "\n";

    for (int i = 0;i < height;i++)
    {
        for (int j = 0; j < width;j++)
        {
            if (j == 0 || j == width - 1) cout << "#";
            else
                if (i == snake.y && j == snake.x)  cout << "O";
                else
                    if (i == point.y && j == point.x) cout << "*";

                    else {
                        bool coada = false;
                        for (int k = 0;k <= ntail;k++)
                        {
                            if (tail[k].x == j && tail[k].y == i) { coada = true; break; }
                        }
                        if (!coada)
                            cout << " ";
                        else cout << "o";
                    }
        }
        cout << "\n";
    }
    for (int i = 0;i < width;i++) cout << "#";
    cout << "\n";
    cout << "Scor:" << scor;
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case'a': dir = left; break;
        case 's':dir = down; break;
        case 'd': dir = right; break;
        case 'w': dir = up; break;
        }
    }

}

void Logic()
{
    switch (dir)
    {
    case left: snake.x--;
        break;
    case right: snake.x++;
        break;
    case down:snake.y++;
        break;
    case up:snake.y--;
        break;
    }
    int xprev, yprev;
    xprev = snake.x;
    yprev = snake.y;
    int xprev2, yprev2;
    for (int i = 0; i <= ntail;i++)
    {
        xprev2 = tail[i].x;
        yprev2 = tail[i].y;
        tail[i].x = xprev;
        tail[i].y = yprev;
        xprev = xprev2;
        yprev = yprev2;
    }

    if (snake.x == point.x && snake.y == point.y)
    {
        scor++;
        ntail++;
        point.x = rand() % width - 1;
        point.y = rand() % height - 1;
    }

    if (snake.x == 0)     GameOver = true;
    if (snake.x == width) GameOver = true;
    if (snake.y == 0)     GameOver = true;
    if (snake.y == height) GameOver = true;

    for (int i = 1; i <= ntail; i++)
    {

        if (snake.x == tail[i].x && snake.y == tail[i].y) { GameOver = true; break; }
    }


}

int main()
{
    Setup();
    while (!GameOver)
    {
        Input();
        Logic();
        Draw();
        Sleep(200);

    }
    return 0;
}
