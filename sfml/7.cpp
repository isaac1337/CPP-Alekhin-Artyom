#include <SFML/Graphics.hpp>
#include <cmath>     

sf::Vector2f normalize(const sf::Vector2f& v)
{
    float length = std::sqrt(v.x * v.x + v.y * v.y);
    if (length != 0.f)
        return sf::Vector2f(v.x / length, v.y / length);
    else
        return sf::Vector2f(0.f, 0.f);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Круг движется за мышью (постоянная скорость)");
    window.setFramerateLimit(60);

    sf::CircleShape circle(30.f);
    circle.setFillColor(sf::Color::Green);
    sf::Vector2f circlePos(400.f, 300.f);
    circle.setPosition(circlePos);

    const float speed = 3.0f;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f mouseWorld = window.mapPixelToCoords(pixelPos);

            sf::Vector2f dir = mouseWorld - circlePos;
            sf::Vector2f dirNorm = normalize(dir);
            circlePos += dirNorm * speed;

            circle.setPosition(circlePos);
        }

        window.clear(sf::Color::Black);
        window.draw(circle);
        window.display();
    }

    return 0;
}
