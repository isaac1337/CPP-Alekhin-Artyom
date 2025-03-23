#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <cmath>

float getRandomFloat(float min, float max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> d(min, max);
    return d(gen);
}

struct Particle
{
    sf::CircleShape shape; 
    float timeAccumulator; 
    float timeThreshold;   
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Броуновское движение");
    window.setFramerateLimit(60);

    const int NUM_PARTICLES = 228;
    std::vector<Particle> particles;
    particles.reserve(NUM_PARTICLES);

    for (int i = 0; i < NUM_PARTICLES; ++i)
    {
        Particle p;
        p.shape.setRadius(5.f);
        p.shape.setOrigin(5.f, 5.f);
        p.shape.setFillColor(sf::Color(
            static_cast<sf::Uint8>(getRandomFloat(0, 255)),
            static_cast<sf::Uint8>(getRandomFloat(0, 255)),
            static_cast<sf::Uint8>(getRandomFloat(0, 255))
        ));
        float x = getRandomFloat(0.f, 800.f);
        float y = getRandomFloat(0.f, 600.f);
        p.shape.setPosition(x, y);

        p.timeAccumulator = 0.f;
        p.timeThreshold   = getRandomFloat(0.3f, 1.5f);

        particles.push_back(p);
    }

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float dt = clock.restart().asSeconds();

        for (auto& p : particles)
        {
            p.timeAccumulator += dt;

            if (p.timeAccumulator >= p.timeThreshold)
            {
                float dx = getRandomFloat(-5.f, 5.f);
                float dy = getRandomFloat(-5.f, 5.f);

                p.shape.move(dx, dy);

                p.timeAccumulator = 0.f;
                p.timeThreshold   = getRandomFloat(0.3f, 1.5f);
            }
        }

        window.clear(sf::Color::Black);
        for (auto& p : particles)
        {
            window.draw(p.shape);
        }
        window.display();
    }

    return 0;
}
