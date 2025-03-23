#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Привет Мир!");

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "ошибочка вышла(" << std::endl;
        return -1;
    }

    sf::Text text;
    text.setFont(font);
    text.setString("Привет Мир!");
    text.setCharacterSize(50);    // размер текста (пиксели)
    text.setFillColor(sf::Color::White);
    text.setPosition(100.f, 100.f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        window.draw(text);

        window.display();
    }

    return 0;
}
