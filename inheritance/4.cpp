#include <iostream>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "button.hpp"

class BaseWindow
{
private:
    static constexpr float dragAreaHeight = 30.0f;
    sf::RenderWindow& mSfmlWindow;
    sf::RectangleShape mBaseRect;
    sf::RectangleShape mDragRect;
    bool mIsDragged {false};
    sf::Vector2f mDragBaseDistance;
    sf::Vector2f mOffset;
public:
    BaseWindow(sf::RenderWindow& window, sf::FloatRect borders)
        : mSfmlWindow(window)
    {
        mDragRect.setPosition({borders.left, borders.top});
        mDragRect.setSize({borders.width, dragAreaHeight});
        mBaseRect.setPosition({borders.left, borders.top + dragAreaHeight});
        mBaseRect.setSize({borders.width, borders.height - dragAreaHeight});
        mDragRect.setFillColor({200, 200, 200});
        mBaseRect.setFillColor({255, 255, 255});
        mDragBaseDistance = mDragRect.getPosition() - mBaseRect.getPosition();
    }
    bool onMousePressed(sf::Vector2f mousePosition)
    {
        if (mDragRect.getGlobalBounds().contains(mousePosition))
        {
            mIsDragged = true;
            mOffset = mousePosition - mDragRect.getPosition();
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
            mDragRect.setPosition(mousePosition - mOffset);
            mBaseRect.setPosition(mDragRect.getPosition() - mDragBaseDistance);
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
    void setBaseColor(sf::Color c)      { mBaseRect.setFillColor(c); }
    void setBaseSize(sf::Vector2f sz)   { mBaseRect.setSize(sz); }
    void setDragColor(sf::Color c)      { mDragRect.setFillColor(c); }
    void setDragSize(sf::Vector2f sz)   { mDragRect.setSize(sz); }
    void setPosition(sf::Vector2f p)
    {
        mBaseRect.setPosition(p);
        mDragRect.setPosition(mBaseRect.getPosition() + mDragBaseDistance);
    }
    void draw() const
    {
        mSfmlWindow.draw(mBaseRect);
        mSfmlWindow.draw(mDragRect);
    }
};

class MessageWindow : public BaseWindow
{
protected:
    sf::Text mText;
    sf::Font mFont;
public:
    MessageWindow(sf::RenderWindow& window, sf::FloatRect borders, const std::string& message)
    : BaseWindow(window, borders)
    {
        if (!mFont.loadFromFile("arial.ttf"))
        {
            std::cerr << "Error loading font\n";
        }
        mText.setFont(mFont);
        mText.setString(message);
        mText.setCharacterSize(18);
        mText.setFillColor(sf::Color::Black);
        mText.setPosition(borders.left + 10, borders.top + 40);
    }
    virtual void handleEvents(const sf::Event& event)
    {
        BaseWindow::handleEvents(event);
    }
    virtual void draw() const
    {
        BaseWindow::draw();
        BaseWindow* constThis = const_cast<BaseWindow*>(static_cast<const BaseWindow*>(this));
        const_cast<sf::RenderWindow&>(static_cast<const sf::RenderWindow&>(dynamic_cast<const sf::RenderWindow&>(*(new sf::RenderWindow)))).draw(mText);
    }
    void draw(sf::RenderWindow& window) const
    {
        BaseWindow::draw();
        window.draw(mText);
    }
};

class ErrorWindow : public MessageWindow
{
public:
    ErrorWindow(sf::RenderWindow& window, sf::FloatRect borders, const std::string& message)
    : MessageWindow(window, borders, message)
    {
        setBaseColor(sf::Color(255, 150, 150));
    }
};

class DoneWindow : public MessageWindow
{
public:
    DoneWindow(sf::RenderWindow& window, sf::FloatRect borders, const std::string& message)
    : MessageWindow(window, borders, message)
    {
        setBaseColor(sf::Color(150, 255, 150));
    }
};

class QuestionWindow : public BaseWindow
{
private:
    sf::Text mText;
    sf::Font mFont;
    Button mOkButton;
    Button mCancelButton;
    sf::FloatRect mBorders;
public:
    QuestionWindow(sf::RenderWindow& window, sf::FloatRect borders, const std::string& message)
    : BaseWindow(window, borders)
    , mOkButton(window, {borders.left + 10, borders.top + borders.height - 40}, {80, 30}, "Ok")
    , mCancelButton(window, {borders.left + borders.width - 90, borders.top + borders.height - 40}, {80, 30}, "Cancel")
    , mBorders(borders)
    {
        if (!mFont.loadFromFile("arial.ttf"))
        {
            std::cerr << "Error loading font\n";
        }
        mText.setFont(mFont);
        mText.setString(message);
        mText.setCharacterSize(18);
        mText.setFillColor(sf::Color::Black);
        mText.setPosition(borders.left + 10, borders.top + 40);
    }
    void handleEvents(const sf::Event& event)
    {
        BaseWindow::handleEvents(event);
        mOkButton.handleEvents(event);
        mCancelButton.handleEvents(event);
        if (mOkButton.isClicked())
            std::cout << "Ok\n";
        if (mCancelButton.isClicked())
            std::cout << "Cancel\n";
    }
    void draw() const
    {
        BaseWindow::draw();
        sf::RenderWindow* window = const_cast<sf::RenderWindow*>(reinterpret_cast<const sf::RenderWindow*>(&mOkButton)); // hack to get window reference from button
        window->draw(mText);
        mOkButton.draw();
        mCancelButton.draw();
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Derived Windows");
    window.setFramerateLimit(60);
    ErrorWindow errorWin(window, {50, 50, 300, 200}, "An error occurred!");
    DoneWindow doneWin(window, {400, 50, 300, 200}, "Operation completed.");
    QuestionWindow questionWin(window, {200, 300, 400, 250}, "Do you want to continue?");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            errorWin.handleEvents(event);
            doneWin.handleEvents(event);
            questionWin.handleEvents(event);
        }
        window.clear(sf::Color::Black);
        errorWin.draw();
        doneWin.draw();
        questionWin.draw();
        window.display();
    }
    return 0;
}
