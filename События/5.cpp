#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "slider.hpp"

int main()
{
    sf::ContextSettings contextSettings;
    contextSettings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 800), "Slider Class! / RGB Circle", sf::Style::Default, contextSettings);
    window.setFramerateLimit(60);

    RectangleSlider rslider(window, {400, 400}, {500, 20}, {25, 90});
    CircleSlider cslider(window, {400, 200}, {500, 20}, 40);
    RectangleSlider rColorSlider(window, {100, 600}, {400, 20}, {0, 255});
    RectangleSlider gColorSlider(window, {100, 630}, {400, 20}, {0, 255});
    RectangleSlider bColorSlider(window, {100, 660}, {400, 20}, {0, 255});
    
    sf::CircleShape circle(100.f);
    circle.setOrigin(100.f, 100.f);
    circle.setPosition(400.f, 300.f);
    circle.setFillColor(sf::Color::White);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            rslider.handleEvent(event);
            cslider.handleEvent(event);
            rColorSlider.handleEvent(event);
            gColorSlider.handleEvent(event);
            bColorSlider.handleEvent(event);
            if (event.type == sf::Event::MouseMoved && (rslider.isPressed() || cslider.isPressed()))
                std::cout << "rslider: " << rslider.getValue() << " | cslider: " << cslider.getValue() << std::endl;
            if (event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
        }
        
        sf::Uint8 red   = static_cast<sf::Uint8>(rColorSlider.getValue());
        sf::Uint8 green = static_cast<sf::Uint8>(gColorSlider.getValue());
        sf::Uint8 blue  = static_cast<sf::Uint8>(bColorSlider.getValue());
        circle.setFillColor(sf::Color(red, green, blue));
        
        window.clear(sf::Color::Black);
        window.draw(circle);
        rslider.draw();
        cslider.draw();
        rColorSlider.draw();
        gColorSlider.draw();
        bColorSlider.draw();
        window.display();
    }
    
    return 0;
}
