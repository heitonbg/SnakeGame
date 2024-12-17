#include <iostream>
#include <conio.h>
#include <windows.h> //слип
#include <vector>
#include <cstdlib>

using namespace std;

bool gameOver; //логическая переменная(показывает завершена ли игра)
const int width = 15; //ширина поля
const int height = 15; //высота поля
int x, y, fruitX, fruitY, score;//переменные для хранения данных
vector<pair<int, int>> snake; //хранение координат всех сегментов нашей анаконды
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };//перечисление направлений змеи
eDirection dir; //переменная, хранящая текущее направление

void Setup() {//загрузочные настройки игры
    gameOver = false; //false - игра окончена, true - не окончена
    dir = STOP;
    x = width / 2; // установление змейки по центру поля
    y = height / 2; // установление змейки по центру поля
    fruitX = rand() % width; //генерация рандомных значений X для фрукта в пределах поля
    fruitY = rand() % height; //генерация рандомных значений Y для фрукта в пределах поля
    score = 0; //начальный счет игрока
    snake.push_back(make_pair(x, y)); //добавляют начальную позицию головы в вектор снейк
}

void Draw() {//функция отрисовки поля
    system("cls"); //очищение консоли для обновления экрана
    for (int i = 0; i < width + 2; i++)
        cout << "#"; //рисование верхней границы поля
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#";//отрисовка поля по левому боку
            if (i == y && j == x)
                cout << "@";//если текущие координаты совпадают с  координатами игрока - выводится голова змеи @
            else if (i == fruitY && j == fruitX)
                cout << "O"; //координаты совпадают с координатами фрукта - отрисовка фрукта O
            else {
                bool print = false; //переменная печати тела
                for (size_t k = 0; k < snake.size(); k++) {
                    if (snake[k].first == j && snake[k].second == i) {
                        cout << "o";
                        print = true;
                    }//если текущие координаты совпадают с одной из координат тела змейки, выводится символ o, и print устанавливается в true.
                }
                if (!print) cout << " ";//если ничего не напечатано - пробел, т.е заполнение поля пустотой
            }
            if (j == width - 1)
                cout << "#";//рисование правой границы поля
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";//нижняя часть поля
    cout << endl << endl;// пробел после игрового поля
    cout << "Score:" << score << endl;//выведение актуального счета игрока
}

void Input() {//функция для обработки нажатий клавиатуры
    if (_kbhit()) {//проверяет нажатие кнопок
        switch (_getch()) {
        case 'a':
            dir = LEFT;//влево
            break;
        case 'd':
            dir = RIGHT;//вправо
            break;
        case 'w':
            dir = UP;//вверх
            break;
        case 's':
            dir = DOWN;//вниз
            break;
        case 'x':
            gameOver = true;//значение x(нажатие x) завершает игру
            break;
        }
    }
}

void Logic() {
    int prevX = snake[0].first;
    int prevY = snake[0].second;//сохранение предыдущих координат змейки
    int prev2X, prev2Y;//дополнительные переменные
    snake[0].first = x;
    snake[0].second = y;//обновление позиций головы змейки

    for (size_t i = 1; i < snake.size(); i++) {
        prev2X = snake[i].first;
        prev2Y = snake[i].second;
        snake[i].first = prevX;
        snake[i].second = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }//цикл обновляет каждую часть тела змейки, перемещая на одну позицию вперед

    switch (dir) {//в зависимости от направления обновляются координаты головы змейки
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

    if (x >= width) x = 0; else if (x < 0) x = width - 1; //если голова уходит за стенку, она появляется с другой стороны
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    for (size_t i = 1; i < snake.size(); i++) {
        if (snake[i].first == x && snake[i].second == y) {
            gameOver = true;
        }//если змейка врезается в свое тело - игра завершается
    }

    if (x == fruitX && y == fruitY) {
        score += 1;
        fruitX = rand() % width;
        fruitY = rand() % height;
        snake.push_back(make_pair(-1, -1));
    }//генерация фрукта и +1 к счетчику score, также если фрукт съеден появляется новый сегмент змейки
}

int main() {//начало основной программы
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100);//игра останавливается на 0.1 секунды
    }
    return 0;
}
