#include <SFML/Graphics.hpp>
#include <time.h>
#define BLOKCS 7
bool isCollide(sf::CircleShape ball, sf::RectangleShape rect1)
{
    return ball.getGlobalBounds().intersects(rect1.getGlobalBounds());
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 600), "Arkanoid-Game");
    srand(time(0));
    window.setFramerateLimit(45);
    window.setPosition(sf::Vector2i(700, 200));
    sf::RectangleShape platform;
    sf::CircleShape ball;
    sf::RectangleShape block;

    platform.setSize(sf::Vector2f(70,30));
    ball.setRadius(10);
    block.setSize(sf::Vector2f(40, 10));

    platform.setFillColor(sf::Color(100,200,40));
    ball.setFillColor(sf::Color(50,50, 150));
    block.setFillColor(sf::Color(50,100,100));

    platform.setPosition(200, 580);
    ball.setPosition(200, 330);

    sf::RectangleShape arr[49];
    int count = 0;
    int n = 0;
    for(int i = 0;i<BLOKCS;i++)
    {
        for(int j = 0;j<BLOKCS;j++)
        {
            arr[count] = block;
            arr[count].setPosition(i*41+40, j*12+80);
            count ++;
        }
    }
    double dx = 6, dy = 5;
    while(window.isOpen())
    {
        sf::Event e;
        while(window.pollEvent(e))
        {
            if(e.type == sf::Event::Closed)
            {
                window.close();
            }

        }
   
    ball.move(dx, 0);
    for(int i = 0;i<BLOKCS*BLOKCS;i++)
    {
        if(isCollide(ball, arr[i]))
        {
            arr[i].setPosition(-100, 0);
            dx = -dx;
        }
    }

    ball.move(0, dy);
    for(int i = 0;i<BLOKCS*BLOKCS;i++)
    {
        if(isCollide(ball, arr[i]))
        {
            arr[i].setPosition(-100, 0);
            dy = -dy;
        }
    }


    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
    {
        if(platform.getPosition().x>=330)
        {

        }
        else
        platform.move(10, 0);
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
    {
        if(platform.getPosition().x <= 0)
        {

        }
        else
            platform.move(-10, 0);
    }
    if(isCollide(ball, platform))
    {
        dy = -dy;
    }


    sf::Vector2f b = ball.getPosition();
    if(b.x<0 || b.x>=390) dx = -dx;
    if(b.y<0 || b.y>=590) dy = -dy;

    //draw//
    
    window.clear(sf::Color::White);
    window.draw(platform); 
    window.draw(ball);
    for(int i = 0;i<BLOKCS*BLOKCS;i++)
    {
        window.draw(arr[i]);
    }
    window.display();
    }

}