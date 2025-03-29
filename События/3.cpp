#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

sf::Color getRandomColor()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<uint8_t> d(0, 255);
    return sf::Color{d(gen), d(gen), d(gen)};
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Создание кругов и изменение цвета");
    window.setFramerateLimit(60);

    std::vector<sf::CircleShape> circles;
    
    constexpr float radius = 30.f;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::CircleShape circle(radius);
                    circle.setFillColor(sf::Color::White);
                    circle.setOrigin(radius, radius);
                    circle.setPosition(static_cast<float>(event.mouseButton.x), 
                                       static_cast<float>(event.mouseButton.y));
                    circles.push_back(circle);
                }
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Space)
                {
                    for(auto& circle : circles)
                    {
                        circle.setFillColor(getRandomColor());
                    }
                }
            }
        }

        window.clear(sf::Color::Black);
        for(const auto& circle : circles)
        {
            window.draw(circle);
        }
        window.display();
    }
    return 0;
}
