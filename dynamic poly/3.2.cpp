#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "widget.hpp"
#include "button.hpp"
#include "slider.hpp"
#include "draggable.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Widgets");
    window.setFramerateLimit(60);
    sf::Font font;
    if (!font.loadFromFile("sourceCodePro.ttf")) return 1;

    std::vector<std::unique_ptr<Widget>> widgets;
    widgets.emplace_back(std::make_unique<Button>(window, sf::IntRect{350,300,200,80}, font, "Cat"));
    widgets.emplace_back(std::make_unique<Button>(window, sf::IntRect{200,450,100,80}, font, "Dog"));
    widgets.emplace_back(std::make_unique<Button>(window, sf::IntRect{600,600,150,70}, font, "Mouse"));
    widgets.emplace_back(std::make_unique<Slider>(window, sf::Vector2f{500,500}, sf::Vector2f{200,10}, sf::Vector2f{20,40}));
    widgets.emplace_back(std::make_unique<Slider>(window, sf::Vector2f{300,100}, sf::Vector2f{250,20}, sf::Vector2f{30,60}));
    widgets.emplace_back(std::make_unique<Draggable>(window, sf::Vector2f{550,100}, sf::Vector2f{200,120}, sf::Vector3f{20,120,50}));
    widgets.emplace_back(std::make_unique<Draggable>(window, sf::Vector2f{50,550}, sf::Vector2f{200,200}, sf::Vector3f{170,20,50}));
    widgets.emplace_back(std::make_unique<Draggable>(window, sf::Vector2f{50,200}, sf::Vector2f{100,100}, sf::Vector3f{100,20,150}));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            for (auto& w : widgets) w->handleEvent(event);
        }
        window.clear(sf::Color::Black);
        for (auto& w : widgets) w->draw();
        window.display();
    }
    return 0;
}
