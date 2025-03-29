#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Toggle
{
public:
    Toggle()
    : m_isOn(false)
    {
        m_size = {80.f, 40.f};

        m_background.setSize(m_size);
        m_background.setFillColor(sf::Color(200, 200, 200)); 
        m_background.setOutlineColor(sf::Color::Black);
        m_background.setOutlineThickness(2.f);


        float knobRadius = m_size.y / 2.f;
        m_knob.setRadius(knobRadius);
        m_knob.setFillColor(sf::Color::White);
        m_knob.setOrigin(knobRadius, knobRadius);

        updateKnobPosition();
    }

    void setPosition(const sf::Vector2f& pos)
    {
        m_background.setPosition(pos);
        updateKnobPosition();
    }

    void setSize(const sf::Vector2f& size)
    {
        m_size = size;
        m_background.setSize(m_size);

        float knobRadius = m_size.y / 2.f;
        m_knob.setRadius(knobRadius);
        m_knob.setOrigin(knobRadius, knobRadius);

        updateKnobPosition();
    }

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window)
    {
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mousePos = window.mapPixelToCoords(
                    sf::Vector2i(event.mouseButton.x, event.mouseButton.y)
                );

                if (m_background.getGlobalBounds().contains(mousePos))
                {
                    // Переключаем состояние
                    m_isOn = !m_isOn;
                    updateAppearance();
                }
            }
        }
    }

    void updateAppearance()
    {
        if (m_isOn)
        {
            m_background.setFillColor(sf::Color(100, 200, 100)); // Зелёный фон
        }
        else
        {
            m_background.setFillColor(sf::Color(200, 200, 200)); // Серый фон
        }
        updateKnobPosition();
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(m_background);
        window.draw(m_knob);
    }

private:
    void updateKnobPosition()
    {
        sf::Vector2f bgPos = m_background.getPosition();
        sf::Vector2f bgSize = m_background.getSize();

        float knobRadius = m_knob.getRadius();

        if (m_isOn)
        {
            m_knob.setPosition(
                bgPos.x + bgSize.x - knobRadius,
                bgPos.y + bgSize.y / 2.f
            );
        }
        else
        {
            // Ползунок слева
            m_knob.setPosition(
                bgPos.x + knobRadius,
                bgPos.y + bgSize.y / 2.f
            );
        }
    }

private:
    bool m_isOn;                      
    sf::RectangleShape m_background;  
    sf::CircleShape m_knob;          
    sf::Vector2f m_size;             
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Toggle Example");
    window.setFramerateLimit(60);

    std::vector<Toggle> toggles(10);

    for (int i = 0; i < 10; ++i)
    {
        float x = 100.f;
        float y = 50.f + i * 60.f; // 60 пикселей между тумблерами
        toggles[i].setPosition({x, y});
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
            else
            {
                for (auto& toggle : toggles)
                {
                    toggle.handleEvent(event, window);
                }
            }
        }

        window.clear(sf::Color::Black);

        for (auto& toggle : toggles)
        {
            toggle.draw(window);
        }
        window.display();
    }

    return 0;
}
