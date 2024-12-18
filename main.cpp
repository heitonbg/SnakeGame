#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <cstdlib>

using namespace std;

bool gameOver;
const int width = 15;
const int height = 15;
int x1, y1, x2, y2, fruitX, fruitY, score1, score2;
vector<pair<int, int>> snake1;
vector<pair<int, int>> snake2;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir1, dir2;

void Setup() {
    gameOver = false;
    dir1 = STOP;
    dir2 = STOP;
    x1 = width / 4;
    y1 = height / 2;
    x2 = (width * 3) / 4;
    y2 = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score1 = 0;
    score2 = 0;
    snake1.push_back(make_pair(x1, y1));
    snake2.push_back(make_pair(x2, y2));
}

void Draw() {
    system("cls");
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#";
            if (i == y1 && j == x1)
                cout << "@";
            else if (i == y2 && j == x2)
                cout << "&";
            else if (i == fruitY && j == fruitX)
                cout << "O";
            else {
                bool print = false;
                for (size_t k = 0; k < snake1.size(); k++) {
                    if (snake1[k].first == j && snake1[k].second == i) {
                        cout << "o";
                        print = true;
                    }
                }
                for (size_t k = 0; k < snake2.size(); k++) {
                    if (snake2[k].first == j && snake2[k].second == i) {
                        cout << "x";
                        print = true;
                    }
                }
                if (!print) cout << " ";
            }
            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl << endl;
    cout << " Player 1 Score: " << score1 << "  Player 2 Score: " << score2 << endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            dir1 = LEFT;
            break;
        case 'd':
            dir1 = RIGHT;
            break;
        case 'w':
            dir1 = UP;
            break;
        case 's':
            dir1 = DOWN;
            break;
        case 'j':
            dir2 = LEFT;
            break;
        case 'l':
            dir2 = RIGHT;
            break;
        case 'i':
            dir2 = UP;
            break;
        case 'k':
            dir2 = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic() {
    int prevX1 = snake1[0].first;
    int prevY1 = snake1[0].second;
    int prev2X1, prev2Y1;
    snake1[0].first = x1;
    snake1[0].second = y1;

    for (size_t i = 1; i < snake1.size(); i++) {
        prev2X1 = snake1[i].first;
        prev2Y1 = snake1[i].second;
        snake1[i].first = prevX1;
        snake1[i].second = prevY1;
        prevX1 = prev2X1;
        prevY1 = prev2Y1;
    }

    switch (dir1) {
    case LEFT:
        x1--;
        break;
    case RIGHT:
        x1++;
        break;
    case UP:
        y1--;
        break;
    case DOWN:
        y1++;
        break;
    default:
        break;
    }

    if (x1 >= width) x1 = 0; else if (x1 < 0) x1 = width - 1;
    if (y1 >= height) y1 = 0; else if (y1 < 0) y1 = height - 1;

    for (size_t i = 1; i < snake1.size(); i++) {
        if (snake1[i].first == x1 && snake1[i].second == y1) {
            gameOver = true;
        }
    }

    for (size_t i = 0; i < snake2.size(); i++) {
        if (snake2[i].first == x1 && snake2[i].second == y1) {
            gameOver = true;
        }
    }

    if (x1 == fruitX && y1 == fruitY) {
        score1 += 1;
        fruitX = rand() % width;
        fruitY = rand() % height;
        snake1.push_back(make_pair(-1, -1));
    }

    int prevX2 = snake2[0].first;
    int prevY2 = snake2[0].second;
    int prev2X2, prev2Y2;
    snake2[0].first = x2;
    snake2[0].second = y2;

    for (size_t i = 1; i < snake2.size(); i++) {
        prev2X2 = snake2[i].first;
        prev2Y2 = snake2[i].second;
        snake2[i].first = prevX2;
        snake2[i].second = prevY2;
        prevX2 = prev2X2;
        prevY2 = prev2Y2;
    }

    switch (dir2) {
    case LEFT:
        x2--;
        break;
    case RIGHT:
        x2++;
        break;
    case UP:
        y2--;
        break;
    case DOWN:
        y2++;
        break;
    default:
        break;
    }

    if (x2 >= width) x2 = 0; else if (x2 < 0) x2 = width - 1;
    if (y2 >= height) y2 = 0; else if (y2 < 0) y2 = height - 1;

    for (size_t i = 1; i < snake2.size(); i++) {
        if (snake2[i].first == x2 && snake2[i].second == y2) {
            gameOver = true;
        }
    }


    for (size_t i = 0; i < snake1.size(); i++) {
        if (snake1[i].first == x2 && snake1[i].second == y2) {
            gameOver = true;
        }
    }

    if (x2 == fruitX && y2 == fruitY) {
        score2 += 1;
        fruitX = rand() % width;
        fruitY = rand() % height;
        snake2.push_back(make_pair(-1, -1));
    }
}

void EndGame() {
    system("cls");
    cout << "Game Over!" << endl;
    cout << "Final Scores:" << endl;
    cout << "Player 1 Score: " << score1 << endl;
    cout << "Player 2 Score: " << score2 << endl;
    _getch();
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100);
    }
    EndGame();
    return 0;
}

