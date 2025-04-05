#include <iostream>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Draggable
{
private:
    sf::RenderWindow& mSfmlWindow;
    sf::RectangleShape mShape;
    bool mIsDragged {false};
    sf::Vector2f mOffset {0.0f, 0.0f};

public:
    Draggable(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size, sf::Color color)
    : mSfmlWindow(window)
    {
        mShape.setPosition(position);
        mShape.setSize(size);
        mShape.setFillColor(color);
    }

    bool onMousePressed(sf::Vector2f mousePosition)
    {
        if (mShape.getGlobalBounds().contains(mousePosition))
        {
            mIsDragged = true;
            mOffset = mousePosition - mShape.getPosition();
        }
        return mIsDragged;
    }

    void onMouseReleased()
    {
        mIsDragged = false;
    }

    void onMouseMoved(sf::Vector2f mousePosition)
    {
        if (mIsDragged)
        {
            mShape.setPosition(mousePosition - mOffset);
        }
    }

    void handleEvents(const sf::Event& event)
    {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mousePosition = mSfmlWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
            onMousePressed(mousePosition);
        }

        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            onMouseReleased();
        }

        if (event.type == sf::Event::MouseMoved)
        {
            sf::Vector2f mousePosition = mSfmlWindow.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
            onMouseMoved(mousePosition);
        }
    }

    void setColor(sf::Color c)
    {
        mShape.setFillColor(c);
    }

    void setSize(sf::Vector2f sz)
    {
        mShape.setSize(sz);
    }

    void setPosition(sf::Vector2f p)
    {
        mShape.setPosition(p);
    }

    void draw() const
    {
        mSfmlWindow.draw(mShape);
    }
};

class DraggableWithColorChange : public Draggable
{
private:
    sf::Color mBaseColor;
    sf::Color mDragColor;
    sf::RenderWindow& mWindow;

public:
    DraggableWithColorChange(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size, sf::Color baseColor, sf::Color dragColor)
    : Draggable(window, position, size, baseColor), mBaseColor(baseColor), mDragColor(dragColor), mWindow(window)
    { }

    void handleEvents(const sf::Event& event)
    {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mousePosition = mWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
            bool dragging = onMousePressed(mousePosition);
            if (dragging)
                setColor(mDragColor);
        }
        else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            onMouseReleased();
            setColor(mBaseColor);
        }
        else if (event.type == sf::Event::MouseMoved)
        {
            sf::Vector2f mousePosition = mWindow.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
            onMouseMoved(mousePosition);
        }
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "DraggableWithColorChange");
    window.setFramerateLimit(60);

    DraggableWithColorChange draggable(window, {100, 100}, {200, 150}, sf::Color(80, 80, 120), sf::Color::Red);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            draggable.handleEvents(event);
        }

        window.clear(sf::Color::Black);
        draggable.draw();
        window.display();
    }

    return 0;
}
