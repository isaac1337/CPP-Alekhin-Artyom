#include <random>
#include <cstdlib>
#include "SFML/Graphics.hpp"
#include "button.hpp"

float getRandomFloat(float a, float b)
{
    static std::random_device rd; static std::mt19937 g(rd());
    std::uniform_real_distribution<float> d(a, b); return d(g);
}
int getRandomInt(int a, int b)
{
    static std::random_device rd; static std::mt19937 g(rd());
    std::uniform_int_distribution<int> d(a, b); return d(g);
}
sf::Color getRandomColor()
{
    static std::random_device rd; static std::mt19937 g(rd());
    std::uniform_int_distribution<sf::Uint8> d; return {d(g), d(g), d(g)};
}

class ShapePool
{
    sf::RectangleShape        mField;
    std::vector<sf::Shape*>   mShapes;
    sf::RenderWindow&         mWnd;
public:
    ShapePool(sf::RenderWindow& w, sf::Vector2f p, sf::Vector2f s): mWnd(w)
    {
        mField.setPosition(p); mField.setSize(s); mField.setFillColor({0,100,200,40});
    }
    void addShape(sf::Shape* s)
    {
        s->setOrigin(s->getGlobalBounds().getSize()/2.f);
        sf::Vector2f mn=s->getGlobalBounds().getSize()/2.f, mx=mField.getSize()-mn;
        s->setPosition(mField.getPosition()+sf::Vector2f(getRandomFloat(mn.x,mx.x),getRandomFloat(mn.y,mx.y)));
        s->setFillColor(getRandomColor()); mShapes.push_back(s);
    }
    size_t size() const {return mShapes.size();}
    sf::Vector2f pos()  const {return mField.getPosition();}
    sf::Vector2f ext()  const {return mField.getSize();}
    sf::Shape& at(size_t i){return *mShapes.at(i);}
    void draw() const {for(auto p:mShapes)mWnd.draw(*p); mWnd.draw(mField);}
    ~ShapePool(){for(auto p:mShapes)delete p;}
};

class Command{public:virtual void execute()=0;virtual~Command()=default;};
class NoCommand:public Command{void execute()override{}};

class RotateCommand:public Command
{
    ShapePool& p; size_t i; float a;
public: RotateCommand(ShapePool& P,size_t I,float A):p(P),i(I),a(A){}
    void execute()override{p.at(i).rotate(a);}
};

class RandomColorCommand:public Command
{
    ShapePool& p; size_t i;
public: RandomColorCommand(ShapePool& P,size_t I):p(P),i(I){}
    void execute()override{p.at(i).setFillColor(getRandomColor());}
};

class RandomAllPositionsCommand:public Command
{
    ShapePool& p;
public: RandomAllPositionsCommand(ShapePool& P):p(P){}
    void execute()override
    {
        for(size_t i=0;i<p.size();++i)
        {
            sf::Shape& s=p.at(i);
            sf::Vector2f mn=s.getGlobalBounds().getSize()/2.f,
                         mx=p.ext()-mn;
            s.setPosition(p.pos()+sf::Vector2f(getRandomFloat(mn.x,mx.x),getRandomFloat(mn.y,mx.y)));
        }
    }
};

class RandomAllColorsCommand:public Command
{
    ShapePool& p;
public: RandomAllColorsCommand(ShapePool& P):p(P){}
    void execute()override
    {
        for(size_t i=0;i<p.size();++i) p.at(i).setFillColor(getRandomColor());
    }
};

class AddNewRandomShape:public Command
{
    ShapePool& p; float mn,mx;
public: AddNewRandomShape(ShapePool& P,float A,float B):p(P),mn(A),mx(B){}
    void execute()override
    {
        int r=getRandomInt(0,2); sf::Shape* s;
        if(r==0) s=new sf::RectangleShape({getRandomFloat(mn,mx),getRandomFloat(mn,mx)});
        else if(r==1) s=new sf::CircleShape(getRandomFloat(mn/2,mx/2));
        else s=new sf::CircleShape(getRandomFloat(mn/2,mx/2),3);
        s->setFillColor(getRandomColor()); s->rotate(getRandomFloat(0,360));
        sf::FloatRect b=s->getGlobalBounds();
        s->setPosition({p.pos().x+getRandomFloat(0,p.ext().x-b.width),
                        p.pos().y+getRandomFloat(0,p.ext().y-b.height)});
        p.addShape(s);
    }
};

class MultiCommand:public Command
{
    std::vector<Command*> cmds;
public:
    explicit MultiCommand(std::vector<Command*> v):cmds(std::move(v)){}
    void execute()override{for(auto c:cmds)c->execute();}
    ~MultiCommand(){for(auto c:cmds)delete c;}
};

class ControlPanel
{
    std::vector<Button*>  btn; std::vector<Command*> cmd; sf::RenderWindow& w;
public:
    explicit ControlPanel(sf::RenderWindow& W):w(W){}
    void add(Button* b,Command* c=new NoCommand){btn.push_back(b);cmd.push_back(c);}
    void draw(){for(auto p:btn)p->draw();}
    void handle(const sf::Event& e)
    {
        for(size_t i=0;i<btn.size();++i) if(btn[i]->handleEvent(e)) cmd[i]->execute();
    }
    ~ControlPanel(){for(auto p:btn)delete p; for(auto p:cmd)delete p;}
};

int main()
{
    sf::ContextSettings st; st.antialiasingLevel=8;
    sf::RenderWindow wnd(sf::VideoMode(800,800),"Shapes and Command",sf::Style::Default,st);

    sf::Font font;
    if(!font.loadFromFile("sourceCodePro.ttf")){std::cerr<<"font\n";return 1;}

    ShapePool pool(wnd,{300,50},{450,700});
    pool.addShape(new sf::RectangleShape({getRandomFloat(50,150),getRandomFloat(50,150)}));
    pool.addShape(new sf::RectangleShape({getRandomFloat(50,150),getRandomFloat(50,150)}));
    pool.addShape(new sf::CircleShape(getRandomFloat(30,100),3));
    pool.addShape(new sf::CircleShape(getRandomFloat(30,100)));
    pool.addShape(new sf::CircleShape(getRandomFloat(30,100)));

    ControlPanel cp(wnd);
    cp.add(new Button(wnd,{40, 80,240,40},font,"Rotate First"), new RotateCommand(pool,0,30));
    cp.add(new Button(wnd,{40,140,240,40},font,"Rotate Second"),new RotateCommand(pool,1,45));
    cp.add(new Button(wnd,{40,200,240,40},font,"One Random Color"),new RandomColorCommand(pool,3));
    cp.add(new Button(wnd,{40,260,240,40},font,"All Random Pos"),  new RandomAllPositionsCommand(pool));
    cp.add(new Button(wnd,{40,320,240,40},font,"New Random Shape"),new AddNewRandomShape(pool,10,150));

    Command* combo=new MultiCommand({
        new RandomAllColorsCommand(pool),
        new RandomAllPositionsCommand(pool)
    });
    cp.add(new Button(wnd,{40,380,240,40},font,"Colors + Pos"),combo);

    cp.add(new Button(wnd,{40,440,240,40},font,"no"));
    cp.add(new Button(wnd,{40,500,240,40},font,"no"));
    cp.add(new Button(wnd,{40,700,240,40},font,"Undo"));

    while(wnd.isOpen())
    {
        sf::Event e;
        while(wnd.pollEvent(e))
        {
            if(e.type==sf::Event::Closed) wnd.close();
            cp.handle(e);
        }
        wnd.clear(sf::Color::Black);
        pool.draw(); cp.draw();
        wnd.display();
    }
    return 0;
}
