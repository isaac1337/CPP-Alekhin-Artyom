#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML: Static Keyboard Check");
    sf::CircleShape circle(50.f);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(175.f, 175.f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            circle.setFillColor(sf::Color::Red);
        else
            circle.setFillColor(sf::Color::Green);

        window.clear();
        window.draw(circle);
        window.display();
    }
    return 0;
}
