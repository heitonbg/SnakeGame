#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <cstdlib>

using namespace std;

bool gameOver;
const int width = 15;
const int height = 15;
int x, y, fruitX, fruitY, score;
vector<pair<int, int>> snake;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    snake.clear();
    snake.push_back(make_pair(x, y));
    snake.push_back(make_pair(x, y + 1));
}

void Draw() {
    system("cls");
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) cout << "#";
            bool printed = false;
            for (size_t k = 0; k < snake.size(); k++) {
                if (snake[k].first == j && snake[k].second == i) {
                    if (k < 2) {
                        cout << "@";
                    } else {
                        cout << "o";
                    }
                    printed = true;
                    break;
                }
            }
            if (!printed) {
                if (fruitX == j && fruitY == i)
                    cout << "O";
                else
                    cout << " ";
            }

            if (j == width - 1) cout << "#";
        }
        cout << endl;
    }
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;
    cout << "Score: " << score << endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            if (dir != RIGHT) dir = LEFT;
            break;
        case 'd':
            if (dir != LEFT) dir = RIGHT;
            break;
        case 'w':
            if (dir != DOWN) dir = UP;
            break;
        case 's':
            if (dir != UP) dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic() {
    vector<pair<int, int>> prev = snake;
    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    if (x >= width) x = 0;
    else if (x < 0) x = width - 1;
    if (y >= height) y = 0;
    else if (y < 0) y = height - 1;
    snake[0] = make_pair(x, y);
    if (dir == RIGHT || dir == LEFT) {
        snake[1] = make_pair(x, y + 1);
    } else if (dir == UP || dir == DOWN) {
        snake[1] = make_pair(x - 1, y);
    }

    if ((x == fruitX && y == fruitY) ||
        (snake[1].first == fruitX && snake[1].second == fruitY)) {
        score++;
        fruitX = rand() % width;
        fruitY = rand() % height;
        snake.push_back(make_pair(-1, -1));
        snake.push_back(make_pair(-1, -1));
    }

    for (size_t i = 2; i < snake.size(); i++) {
        snake[i] = prev[i - 2];
    }

    for (size_t i = 2; i < snake.size(); i++) {
        if ((snake[i] == snake[0] || snake[i] == snake[1]) && prev[i] != snake[0] && prev[i] != snake[1]) {
            gameOver = true;
        }
    }
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100);
    }
    return 0;
}
