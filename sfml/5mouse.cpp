#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>       // для std::to_string

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mouse Coordinates");

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Ошибочка вышла(" << std::endl;
        return -1;
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(10.f, 10.f); 

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);

        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

        std::string output = "Pixel coords: ("
                             + std::to_string(pixelPos.x) + ", "
                             + std::to_string(pixelPos.y) + ")\n"
                             "World coords: ("
                             + std::to_string(worldPos.x) + ", "
                             + std::to_string(worldPos.y) + ")";

        text.setString(output);

        window.clear(sf::Color::Black);

        window.draw(text);

        window.display();
    }

    return 0;
}
