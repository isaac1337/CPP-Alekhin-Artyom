#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class Widget {
public:
    virtual void handleEvent(const sf::Event& event) = 0;
    virtual void draw() = 0;
    virtual ~Widget() = default;
};
