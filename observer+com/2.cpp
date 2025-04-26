#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <functional>
#include <memory>
#include <set>
#include <vector>

class Observer {
public:
    virtual void update(float v) = 0;
    virtual ~Observer() = default;
};

class Drawable {
public:
    virtual void draw() const = 0;
    virtual ~Drawable() = default;
};

class Slider : public Drawable {
    sf::RectangleShape  mTrack;
    sf::RectangleShape  mThumb;
    sf::RenderWindow&   mWnd;
    bool                mPressed{false};
    std::set<Observer*> mObservers;

public:
    Slider(sf::RenderWindow& w, sf::Vector2f pos, sf::Vector2f track, sf::Vector2f thumb)
        : mWnd(w) {
        mTrack.setSize(track);
        mTrack.setOrigin(track / 2.f);
        mTrack.setPosition(pos);
        mTrack.setFillColor({200, 200, 220});
        mThumb.setSize(thumb);
        mThumb.setOrigin(thumb / 2.f);
        mThumb.setPosition(pos);
        mThumb.setFillColor({150, 150, 240});
    }

    void addObserver(Observer* p) { mObservers.insert(p); }

    float value() const {
        float part = mThumb.getPosition().x -
                     (mTrack.getPosition().x - mTrack.getSize().x / 2.f);
        return part / mTrack.getSize().x * 100.f;
    }

    void draw() const override {
        mWnd.draw(mTrack);
        mWnd.draw(mThumb);
    }

    void handleEvent(const sf::Event& e) {
        if (e.type == sf::Event::MouseMoved)
            mouseMove(e);
        else if (e.type == sf::Event::MouseButtonPressed)
            mousePress(e);
        else if (e.type == sf::Event::MouseButtonReleased)
            mPressed = false;
    }

private:
    void mouseMove(const sf::Event& e) {
        if (!mPressed) return;
        sf::Vector2f m =
            mWnd.mapPixelToCoords({e.mouseMove.x, e.mouseMove.y});
        float min = mTrack.getPosition().x - mTrack.getSize().x / 2.f;
        float max = mTrack.getPosition().x + mTrack.getSize().x / 2.f;
        mThumb.setPosition(
            {std::clamp(m.x, min, max), mThumb.getPosition().y});
        notify();
    }

    void mousePress(const sf::Event& e) {
        if (e.mouseButton.button != sf::Mouse::Left) return;
        sf::Vector2f m =
            mWnd.mapPixelToCoords({e.mouseButton.x, e.mouseButton.y});
        if (mThumb.getGlobalBounds().contains(m) ||
            mTrack.getGlobalBounds().contains(m)) {
            mPressed = true;
            mThumb.setPosition({m.x, mThumb.getPosition().y});
            notify();
        }
    }

    void notify() {
        float v = value();
        for (auto* p : mObservers) p->update(v);
    }
};

class Circle : public Drawable {
    sf::CircleShape   mShape;
    sf::RenderWindow& mWnd;

public:
    Circle(sf::RenderWindow& w, sf::Vector2f pos, float r) : mWnd(w) {
        mShape.setRadius(r);
        mShape.setOrigin(r, r);
        mShape.setPosition(pos);
        mShape.setFillColor(sf::Color::Green);
    }

    void draw() const override { mWnd.draw(mShape); }
    sf::Shape& shape() { return mShape; }
};

class Square : public Drawable {
    sf::RectangleShape mShape;
    sf::RenderWindow&  mWnd;

public:
    Square(sf::RenderWindow& w, sf::Vector2f pos, float size) : mWnd(w) {
        mShape.setSize({size, size});
        mShape.setOrigin(size / 2.f, size / 2.f);
        mShape.setPosition(pos);
        mShape.setFillColor(sf::Color::Red);
    }

    void draw() const override { mWnd.draw(mShape); }
    sf::Shape& shape() { return mShape; }
};

class ObserverFn : public Observer {
    std::function<void(float)> mFn;

public:
    explicit ObserverFn(std::function<void(float)> fn) : mFn(std::move(fn)) {}
    void update(float v) override { mFn(v); }
};

int main() {
    sf::ContextSettings s;
    s.antialiasingLevel = 8;
    sf::RenderWindow wnd(sf::VideoMode(800, 800), "Two-Slider Observer",
                         sf::Style::Default, s);
    wnd.setFramerateLimit(60);

    Slider rotSlider
