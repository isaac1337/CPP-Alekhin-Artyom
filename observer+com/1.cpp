#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <set>

class Observer
{
public:
    virtual void update(float value) = 0;
    virtual ~Observer() = default;
};

class Subject
{
public:
    virtual void addObserver(Observer* p)    = 0;
    virtual void removeObserver(Observer* p) = 0;
    virtual void notifyObservers()           = 0;
    virtual ~Subject() = default;
};

class Drawable
{
public:
    virtual void draw() const = 0;
    virtual ~Drawable() = default;
};

class Slider : public Drawable, public Subject
{
    sf::RectangleShape mTrackShape {};
    sf::RectangleShape mThumbShape {};
    sf::Color mTrackColor {200, 200, 220};
    sf::Color mThumbColor {150, 150, 240};
    sf::RenderWindow& mRenderWindow;
    bool mIsPressed {false};
    std::set<Observer*> mObservers;

public:
    Slider(sf::RenderWindow& window, sf::Vector2f centerPosition, sf::Vector2f trackSize, sf::Vector2f thumbSize)
    : mRenderWindow(window)
    {
        mTrackShape.setSize(trackSize);
        mTrackShape.setOrigin(trackSize / 2.0f);
        mTrackShape.setPosition(centerPosition);
        mTrackShape.setFillColor(mTrackColor);

        mThumbShape.setSize(thumbSize);
        mThumbShape.setOrigin(thumbSize / 2.0f);
        mThumbShape.setPosition(centerPosition);
        mThumbShape.setFillColor(mThumbColor);
    }

    void draw() const override
    {
        mRenderWindow.draw(mTrackShape);
        mRenderWindow.draw(mThumbShape);
    }

    void onMouseMove(const sf::Event& event)
    {
        if (!mIsPressed) return;
        sf::Vector2f mousePos = mRenderWindow.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
        float min = mTrackShape.getPosition().x - mTrackShape.getSize().x / 2.f;
        float max = mTrackShape.getPosition().x + mTrackShape.getSize().x / 2.f;
        mThumbShape.setPosition({std::clamp(mousePos.x, min, max), mThumbShape.getPosition().y});
        notifyObservers();
    }

    void onMousePressed(const sf::Event& event)
    {
        if (event.mouseButton.button != sf::Mouse::Left) return;
        sf::Vector2f mousePos = mRenderWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
        if (mThumbShape.getGlobalBounds().contains(mousePos) || mTrackShape.getGlobalBounds().contains(mousePos))
        {
            mIsPressed = true;
            mThumbShape.setPosition({mousePos.x, mThumbShape.getPosition().y});
            notifyObservers();
        }
    }

    void onMouseReleased(const sf::Event&) { mIsPressed = false; }

    void handleEvent(const sf::Event& event)
    {
        if      (event.type == sf::Event::MouseMoved)          onMouseMove(event);
        else if (event.type == sf::Event::MouseButtonPressed)  onMousePressed(event);
        else if (event.type == sf::Event::MouseButtonReleased) onMouseReleased(event);
    }

    float getValue() const
    {
        float part = mThumbShape.getPosition().x - (mTrackShape.getPosition().x - mTrackShape.getSize().x / 2.f);
        return part / mTrackShape.getSize().x * 100.f;
    }

    void addObserver(Observer* p)    override { mObservers.insert(p); }
    void removeObserver(Observer* p) override { mObservers.erase(p);  }

    void notifyObservers() override
    {
        float v
