#include <random>
#include <cstdlib>
#include "SFML/Graphics.hpp"
#include "button.hpp"

float getRandomFloat(float min, float max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> d(min, max);
    return d(gen);
}

int getRandomInt(int min, int max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> d(min, max);
    return d(gen);
}

sf::Color getRandomColor()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<sf::Uint8> d;
    return sf::Color(d(gen), d(gen), d(gen));
}

class ShapePool
{
    sf::RectangleShape        mField;
    std::vector<sf::Shape*>   mShapes;
    sf::RenderWindow&         mWnd;

public:
    ShapePool(sf::RenderWindow& w, sf::Vector2f pos, sf::Vector2f size) : mWnd(w)
    {
        mField.setPosition(pos);
        mField.setSize(size);
        mField.setFillColor(sf::Color(0, 100, 200, 40));
    }

    void addShape(sf::Shape* p)
    {
        p->setOrigin(p->getGlobalBounds().getSize() / 2.f);
        sf::Vector2f min = p->getGlobalBounds().getSize() / 2.f;
        sf::Vector2f max = mField.getSize() - p->getGlobalBounds().getSize() / 2.f;
        p->setPosition(mField.getPosition() +
                       sf::Vector2f(getRandomFloat(min.x, max.x), getRandomFloat(min.y, max.y)));
        p->setFillColor(getRandomColor());
        mShapes.push_back(p);
    }

    void clear()
    {
        for (auto* p : mShapes) delete p;
        mShapes.clear();
    }

    size_t       getNumbeorOfShapes() const { return mShapes.size(); }
    sf::Vector2f getPosition()        const { return mField.getPosition(); }
    sf::Vector2f getSize()            const { return mField.getSize(); }

    sf::Shape& getShape(size_t i) { return *mShapes.at(i); }

    void draw() const
    {
        for (auto p : mShapes) mWnd.draw(*p);
        mWnd.draw(mField);
    }

    ~ShapePool() { clear(); }
};

class Command { public: virtual void execute() = 0; virtual ~Command() = default; };
class NoCommand : public Command { void execute() override {} };

class RotateCommand : public Command
{
    ShapePool& mPool; size_t mIdx; float mAng;
public:
    RotateCommand(ShapePool& p, size_t i, float a) : mPool(p), mIdx(i), mAng(a) {}
    void execute() override { mPool.getShape(mIdx).rotate(mAng); }
};

class RandomColorCommand : public Command
{
    ShapePool& mPool; size_t mIdx;
public:
    RandomColorCommand(ShapePool& p, size_t i) : mPool(p), mIdx(i) {}
    void execute() override { mPool.getShape(mIdx).setFillColor(getRandomColor()); }
};

class RandomAllPositionsCommand : public Command
{
    ShapePool& mPool;
public:
    RandomAllPositionsCommand(ShapePool& p) : mPool(p) {}
    void execute() override
    {
        for (size_t i = 0; i < mPool.getNumbeorOfShapes(); ++i)
        {
            sf::Shape& s = mPool.getShape(i);
            sf::Vector2f min = s.getGlobalBounds().getSize() / 2.f;
            sf::Vector2f max = mPool.getSize() - s.getGlobalBounds().getSize() / 2.f;
            s.setPosition(mPool.getPosition() +
                          sf::Vector2f(getRandomFloat(min.x, max.x), getRandomFloat(min.y, max.y)));
        }
    }
};

class AddNewRandomShape : public Command
{
    ShapePool& mPool; float mMin; float mMax;
public:
    AddNewRandomShape(ShapePool& p, float mn, float mx) : mPool(p), mMin(mn), mMax(mx) {}
    void execute() override
    {
        int r = getRandomInt(0, 2);
        sf::Shape* ps;
        if (r == 0)
            ps = new sf::RectangleShape({getRandomFloat(mMin, mMax), getRandomFloat(mMin, mMax)});
        else if (r == 1)
            ps = new sf::CircleShape(getRandomFloat(mMin / 2, mMax / 2));
        else
            ps = new sf::CircleShape(getRandomFloat(mMin / 2, mMax / 2), 3);

        ps->setFillColor(getRandomColor());
        ps->rotate(getRandomFloat(0, 360));
        sf::FloatRect b = ps->getGlobalBounds();
        ps->setPosition({mPool.getPosition().x + getRandomFloat(0, mPool.getSize().x - b.width),
                         mPool.getPosition().y + getRandomFloat(0, mPool.getSize().y - b.height)});
        mPool.addShape(ps);
    }
};

class RemoveAllShapesCommand : public Command
{
    ShapePool& mPool;
public:
    explicit RemoveAllShapesCommand(ShapePool& p) : mPool(p) {}
    void execute() override { mPool.clear(); }
};

class ControlPanel
{
    std::vector<Button*>  mButtons;
    std::vector<Command*> mCommands;
    sf::RenderWindow&     mWnd;
public:
    explicit ControlPanel(sf::RenderWindow& w) : mWnd(w) {}

    void addButton(Button* b) { mButtons.push_back(b); mCommands.push_back(new NoCommand); }
    void addButton(Button* b, Command* c) { mButtons.push_back(b); mCommands.push_back(c); }

    void draw() { for (auto* p : mButtons) p->draw(); }

    void handleEvent(const sf::Event& e)
    {
        for (size_t i = 0; i < mButtons.size(); ++i)
            if (mButtons[i]->handleEvent(e)) mCommands[i]->execute();
    }

    ~ControlPanel()
    {
        for (auto* p : mButtons)  delete p;
        for (auto* p : mCommands) delete p;
    }
};

int main()
{
    sf::ContextSettings st; st.antialiasingLevel = 8;
    sf::RenderWindow wnd(sf::VideoMode(800, 800), "Shapes and Command", sf::Style::Default, st);

    sf::Font font;
    if (!font.loadFromFile("sourceCodePro.ttf"))
    {
        std::cerr << "Can't load font\n"; return 1;
    }

    ShapePool pool(wnd, {300, 50}, {450, 700});
    pool.addShape(new sf::RectangleShape({getRandomFloat(50, 150), getRandomFloat(50, 150)}));
    pool.addShape(new sf::RectangleShape({getRandomFloat(50, 150), getRandomFloat(50, 150)}));
    pool.addShape(new sf::CircleShape(getRandomFloat(30, 100), 3));
    pool.addShape(new sf::CircleShape(getRandomFloat(30, 100)));
    pool.addShape(new sf::CircleShape(getRandomFloat(30, 100)));

    ControlPanel cp(wnd);
    cp.addButton(new Button(wnd, {40,  80, 240, 40}, font, "Rotate First"),         new RotateCommand(pool, 0, 30));
    cp.addButton(new Button(wnd, {40, 140, 240, 40}, font, "Rotate Second"),        new RotateCommand(pool, 1, 45));
    cp.addButton(new Button(wnd, {40, 200, 240, 40}, font, "One Random Color"),     new RandomColorCommand(pool, 3));
    cp.addButton(new Button(wnd, {40, 260, 240, 40}, font, "All Random Positions"), new RandomAllPositionsCommand(pool));
    cp.addButton(new Button(wnd, {40, 320, 240, 40}, font, "New Random Shape"),     new AddNewRandomShape(pool, 10, 150));
    cp.addButton(new Button(wnd, {40, 380, 240, 40}, font, "Delete All"),           new RemoveAllShapesCommand(pool));
    cp.addButton(new Button(wnd, {40, 440, 240, 40}, font, "no"));
    cp.addButton(new Button(wnd, {40, 500, 240, 40}, font, "no"));
    cp.addButton(new Button(wnd, {40, 700, 240, 40}, font, "Undo"));

    while (wnd.isOpen())
    {
        sf::Event e;
        while (wnd.pollEvent(e))
        {
            if (e.type == sf::Event::Closed) wnd.close();
            cp.handleEvent(e);
        }
        wnd.clear(sf::Color::Black);
        pool.draw();
        cp.draw();
        wnd.display();
    }
    return 0;
}
