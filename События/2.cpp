#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 400), "SFML: Mouse Collision - Static Method");
    
    sf::RectangleShape rectangle(sf::Vector2f(200.f, 150.f));
    rectangle.setPosition(200.f, 125.f);
    rectangle.setFillColor(sf::Color::Green);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
        }
        
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        
        if (rectangle.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
            rectangle.setFillColor(sf::Color::Red);
        else
            rectangle.setFillColor(sf::Color::Green);
        
        window.clear();
        window.draw(rectangle);
        window.display();
    }
    
    return 0;
}
