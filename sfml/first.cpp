#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Вращающийся квадрат");
    window.setFramerateLimit(60);

    sf::RectangleShape square(sf::Vector2f(100.f, 100.f));
    square.setFillColor(sf::Color::Green);
    square.setOrigin(50.f, 50.f);
    square.setPosition(400.f, 300.f);

    float angle = 0.f;
    float rotationSpeed = 90.f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        angle += rotationSpeed * (1.f / 60.f);
        if (angle >= 360.f) {
            angle -= 360.f;
        }

        square.setRotation(angle);

        window.clear(sf::Color::Black);
        window.draw(square);
        window.display();
    }

    return 0;
}
