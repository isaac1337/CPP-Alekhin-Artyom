#include <random>
#include <cstdlib>
#include <memory>
#include "SFML/Graphics.hpp"
#include "button.hpp"

float rndf(float a, float b) { static std::mt19937 g{std::random_device{}()}; return std::uniform_real_distribution<float>(a, b)(g); }
int   rndi(int a, int b)    { static std::mt19937 g{std::random_device{}()}; return std::uniform_int_distribution<int>(a, b)(g); }
sf::Color rndColor()        { static std::mt19937 g{std::random_device{}()}; return {static_cast<sf::Uint8>(rndi(0,255)),static_cast<sf::Uint8>(rndi(0,255)),static_cast<sf::Uint8>(rndi(0,255))}; }

class ShapePool
{
    sf::RectangleShape        field;
    std::vector<sf::Shape*>   shapes;
    sf::RenderWindow&         wnd;
public:
    ShapePool(sf::RenderWindow& w,sf::Vector2f p,sf::Vector2f s):wnd(w)
    { field.setPosition(p); field.setSize(s); field.setFillColor({0,100,200,40}); }
    void addShape(sf::Shape* s)
    {
        s->setOrigin(s->getGlobalBounds().getSize()/2.f);
        auto mn=s->getGlobalBounds().getSize()/2.f, mx=field.getSize()-mn;
        s->setPosition(field.getPosition()+sf::Vector2f(rndf(mn.x,mx.x),rndf(mn.y,mx.y)));
        s->setFillColor(rndColor()); shapes.push_back(s);
    }
    void removeLast() { if(!shapes.empty()){ delete shapes.back(); shapes.pop_back(); } }
    size_t  size()const{return shapes.size();}
    sf::Shape& at(size_t i){return *shapes.at(i);}
    sf::Vector2f pos()const{return field.getPosition();}
    sf::Vector2f ext()const{return field.getSize();}
    void draw()const{for(auto p:shapes) wnd.draw(*p); wnd.draw(field);}
    ~ShapePool(){for(auto p:shapes) delete p;}
};

class Command{
public:
    virtual void execute()   =0;
    virtual void unexecute() =0;
    virtual Command* clone() const =0;
    virtual ~Command()=default;
};
using CmdPtr = Command*;

class RotateCommand:public Command
{
    ShapePool& pool; size_t idx; float angle;
public:
    RotateCommand(ShapePool& p,size_t i,float a):pool(p),idx(i),angle(a){}
    void execute()   override{ pool.at(idx).rotate(angle); }
    void unexecute() override{ pool.at(idx).rotate(-angle); }
    CmdPtr clone() const override{ return new RotateCommand(*this); }
};

class RandomColorCommand:public Command
{
    ShapePool& pool; size_t idx; sf::Color prev;
public:
    RandomColorCommand(ShapePool& p,size_t i):pool(p),idx(i){}
    void execute() override{ prev=pool.at(idx).getFillColor(); pool.at(idx).setFillColor(rndColor()); }
    void unexecute() override{ pool.at(idx).setFillColor(prev); }
    CmdPtr clone()const override{ return new RandomColorCommand(*this); }
};

class RandomAllColorsCommand:public Command
{
    ShapePool& pool; std::vector<sf::Color> prev;
public:
    RandomAllColorsCommand(ShapePool& p):pool(p){}
    void execute() override
    {
        prev.clear(); prev.reserve(pool.size());
        for(size_t i=0;i<pool.size();++i){ prev.push_back(pool.at(i).getFillColor()); pool.at(i).setFillColor(rndColor());}
    }
    void unexecute() override { for(size_t i=0;i<prev.size();++i) pool.at(i).setFillColor(prev[i]); }
    CmdPtr clone()const override{ return new RandomAllColorsCommand(*this); }
};

class RandomAllPositionsCommand:public Command
{
    ShapePool& pool; std::vector<sf::Vector2f> prev;
public:
    RandomAllPositionsCommand(ShapePool& p):pool(p){}
    void execute() override
    {
        prev.clear(); prev.reserve(pool.size());
        for(size_t i=0;i<pool.size();++i)
        {
            prev.push_back(pool.at(i).getPosition());
            sf::Shape& s=pool.at(i);
            auto mn=s.getGlobalBounds().getSize()/2.f, mx=pool.ext()-mn;
            s.setPosition(pool.pos()+sf::Vector2f(rndf(mn.x,mx.x),rndf(mn.y,mx.y)));
        }
    }
    void unexecute() override{ for(size_t i=0;i<prev.size();++i) pool.at(i).setPosition(prev[i]); }
    CmdPtr clone()const override{ return new RandomAllPositionsCommand(*this); }
};

class AddNewRandomShape:public Command
{
    ShapePool& pool; float mn,mx; bool executed{false};
public:
    AddNewRandomShape(ShapePool& p,float a,float b):pool(p),mn(a),mx(b){}
    void execute() override
    {
        int r=rndi(0,2); sf::Shape* s;
        if(r==0) s=new sf::RectangleShape({rndf(mn,mx),rndf(mn,mx)});
        else if(r==1) s=new sf::CircleShape(rndf(mn/2,mx/2));
        else          s=new sf::CircleShape(rndf(mn/2,mx/2),3);
        pool.addShape(s); executed=true;
    }
    void unexecute() override{ if(executed){ pool.removeLast(); executed=false; } }
    CmdPtr clone()const override{ return new AddNewRandomShape(*this); }
};

class MultiCommand:public Command
{
    std::vector<CmdPtr> proto; std::vector<CmdPtr> execs;
public:
    explicit MultiCommand(std::vector<CmdPtr> p):proto(p){}
    void execute() override
    {
        execs.clear();
        for(auto pr:proto){ CmdPtr c=pr->clone(); c->execute(); execs.push_back(c); }
    }
    void unexecute() override
    {
        for(auto it=execs.rbegin(); it!=execs.rend(); ++it){ (*it)->unexecute(); delete *it; }
        execs.clear();
    }
    CmdPtr clone() const override
    {
        std::vector<CmdPtr> pc; for(auto pr:proto) pc.push_back(pr->clone());
        return new MultiCommand(std::move(pc));
    }
    ~MultiCommand(){ for(auto p:proto) delete p; for(auto p:execs) delete p; }
};

class ControlPanel
{
    std::vector<Button*> buttons;
    std::vector<CmdPtr>  proto;
    std::vector<CmdPtr>  history;
    sf::RenderWindow&    wnd;
public:
    explicit ControlPanel(sf::RenderWindow& w):wnd(w){}
    void add(Button* b,CmdPtr p){ buttons.push_back(b); proto.push_back(p); }
    void draw(){ for(auto b:buttons) b->draw(); }
    void handle(const sf::Event& e)
    {
        for(size_t i=0;i<buttons.size();++i)
            if(buttons[i]->handleEvent(e))
            {
                if(dynamic_cast<class UndoCommand*>(proto[i])) proto[i]->execute();
                else { CmdPtr c=proto[i]->clone(); c->execute(); history.push_back(c); }
            }
    }
    std::vector<CmdPtr>& getHistory(){ return history; }
    ~ControlPanel(){ for(auto b:buttons) delete b; for(auto p:proto) delete p; for(auto h:history) delete h; }
};

class UndoCommand:public Command
{
    ControlPanel& panel;
public:
    explicit UndoCommand(ControlPanel& p):panel(p){}
    void execute() override
    {
        auto& hist=panel.getHistory();
        if(hist.empty()) return;
        CmdPtr c=hist.back(); hist.pop_back(); c->unexecute(); delete c;
    }
    void unexecute() override {}
    CmdPtr clone() const override{ return new UndoCommand(panel); }
};

int main()
{
    sf::ContextSettings st; st.antialiasingLevel=8;
    sf::RenderWindow wnd(sf::VideoMode(800,800),"Shapes with Undo",sf::Style::Default,st);

    sf::Font font; if(!font.loadFromFile("sourceCodePro.ttf")) return 1;

    ShapePool pool(wnd,{300,50},{450,700});
    pool.addShape(new sf::RectangleShape({rndf(50,150),rndf(50,150)}));
    pool.addShape(new sf::RectangleShape({rndf(50,150),rndf(50,150)}));
    pool.addShape(new sf::CircleShape(rndf(30,100),3));
    pool.addShape(new sf::CircleShape(rndf(30,100)));

    ControlPanel cp(wnd);
    cp.add(new Button(wnd,{40, 80,240,40},font,"Rotate First"), new RotateCommand(pool,0,30));
    cp.add(new Button(wnd,{40,140,240,40},font,"Random Color"), new RandomColorCommand(pool,1));
    cp.add(new Button(wnd,{40,200,240,40},font,"Random Pos"),   new RandomAllPositionsCommand(pool));
    cp.add(new Button(wnd,{40,260,240,40},font,"Add Shape"),    new AddNewRandomShape(pool,10,150));
    cp.add(new Button(wnd,{40,320,240,40},font,"Color + Pos"),
           new MultiCommand({ new RandomAllColorsCommand(pool), new RandomAllPositionsCommand(pool) }));
    cp.add(new Button(wnd,{40,700,240,40},font,"Undo"),         new UndoCommand(cp));

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
