#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
using namespace sf;

const int M = 20;
const int N = 10;

int field[M][N] = {0};

typedef struct Point
{
    int x;
    int y;
} Point;

Point a[4];
Point b[4];

int figures[7][4] =
    {
        1, 3, 5, 7,
        2, 4, 5, 7,
        3, 5, 4, 6,
        3, 5, 4, 7,
        2, 3, 5, 7,
        3, 5, 7, 6,
        2, 3, 4, 5,
};

bool check()
{
    for (int i = 0; i < 4; i++)
    {
        if (a[i].x < 0 || a[i].x >= N || a[i].y >= M)
            return 0;
        else if (field[a[i].y][a[i].x]) // проверка на ненулевое поле
            return 0;
    }
    return 1;
}
using namespace sf;

int main()
{
    srand(time(0));
    RenderWindow window(VideoMode(320, 480), "The Game!");

    RectangleShape rect;
    rect.setFillColor(Color(0, 255, 100));
    rect.setSize(Vector2f(20, 20));

    int dx = 0;
    bool rotate = false;

    int colorNum = 1;
    float timer = 0;
    float delay = 0.3;
    int n = 3;
    Clock clock;
    for (int i = 0; i < 4; i++) // какой то гений
    {
        a[i].x = figures[n][i] % 2;
        a[i].y = figures[n][i] / 2;
    }
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    rotate = true;
                    break;
                case sf::Keyboard::Left:
                    dx = -1;
                    break;
                case sf::Keyboard::Right:
                    dx = 1;
                    break;
                case sf::Keyboard::Down:
                    delay = 0.05;
                default:
                    break;
                }
            }
        }
        // Move//
        for (int i = 0; i < 4; i++)
        {
            b[i] = a[i];
            a[i].x += dx;
        }
        if (!check())
            for (int i = 0; i < 4; i++)
            {
                a[i] = b[i];
            }

        if (rotate)
        {
            Point p = a[1]; // center of rotation
            for (int i = 0; i < 4; i++)
            {
                int x = a[i].y - p.y;
                int y = a[i].x - p.x;
                a[i].x = p.x - x;
                a[i].y = p.y + y;
            }
            if (!check())
            {
                for (int i = 0; i < 4; i++)
                {
                    a[i] = b[i];
                }
            }
        }

        // tick//
        if (timer > delay)
        {
            for (int i = 0; i < 4; i++)
            {
                a[i].y += 1;
            }
            if (!check())
            {
                for (int i = 0; i < 4; i++)
                {
                    field[b[i].y][b[i].x] = colorNum; // если достигнута граница то заполняем ячейки поля ненулевыми значениями
                }
                colorNum = 1 + rand() % 7;
                n = rand() % 7; // Выбираем след. фигуру
                for (int i = 0; i < 4; i++)//Запускаем некст фигуру
                {
                    a[i].x = figures[n][i] % 2;
                    a[i].y = figures[n][i] / 2;
                }
            }
            timer = 0;
        }
        dx = 0;
        rotate = false;
        delay = 0.3;

        ///check lines///
        int k = M-1;
        for(int i = M-1;i> 0 ;i--)
        {
            int count = 0;
            for(int j = 0;j<N;j++)
            {
                if(field[i][j])
                count++;
                field[k][j] = field[i][j];//верхние свободные блоки затирают нижние
            }
            if(count <N) k--;
            
        }
        /// draw///
        window.clear(Color::White);

        for(int i = 0;i<M;i++)
        {
            for(int j = 0;j<N;j++)
            {
                if(field[i][j] == 0)
                {

                }
                else{
                    rect.setPosition(j*20, i*20);
                    window.draw(rect);
                }
            }
        }

        for (int i = 0; i < 4; i++)
        {
            rect.setPosition(a[i].x * 20, a[i].y * 20);
            window.draw(rect);
        }

        window.display();
    }

    return 0;
}