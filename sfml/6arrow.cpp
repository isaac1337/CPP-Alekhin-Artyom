#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Движение при помощи стрелочек");

    sf::CircleShape circle(50);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(100.f, 100.f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        const float moveSpeed = 5.f; 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            circle.move(-moveSpeed, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            circle.move(moveSpeed, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            circle.move(0.f, -moveSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            circle.move(0.f, moveSpeed);
        }

        window.clear(sf::Color::Black);

        window.draw(circle);

        window.display();
    }

    return 0;
}
