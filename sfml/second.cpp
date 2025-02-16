#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

const float WIDTH = 800.f;
const float HEIGHT = 600.f;
const float MIN_DISTANCE = 10.f;
const float TIME_STEP = 1.f / 60.f;

struct Ball {
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float mass;
    float charge;

    Ball(float x, float y, float mass, float charge) {
        this->mass = mass;
        this->charge = charge;
        velocity = {0.f, 0.f};
        shape.setRadius(10.f);
        shape.setOrigin(10.f, 10.f);
        shape.setPosition(x, y);
        shape.setFillColor(charge > 0 ? sf::Color::Red : sf::Color::Blue);
    }

    void updatePosition() {
        shape.move(velocity * TIME_STEP);
    }

    void checkCollisionWithWalls() {
        if (shape.getPosition().x - shape.getRadius() < 0 || shape.getPosition().x + shape.getRadius() > WIDTH) {
            velocity.x = -velocity.x;
        }
        if (shape.getPosition().y - shape.getRadius() < 0 || shape.getPosition().y + shape.getRadius() > HEIGHT) {
            velocity.y = -velocity.y;
        }
    }
};

float calculateDistance(const sf::Vector2f& pos1, const sf::Vector2f& pos2) {
    return std::sqrt(std::pow(pos2.x - pos1.x, 2) + std::pow(pos2.y - pos1.y, 2));
}

sf::Vector2f calculateForce(const Ball& b1, const Ball& b2) {
    sf::Vector2f direction = b2.shape.getPosition() - b1.shape.getPosition();
    float distance = calculateDistance(b1.shape.getPosition(), b2.shape.getPosition());
    if (distance < MIN_DISTANCE) return {0.f, 0.f};
    direction /= distance;
    float forceMagnitude = b1.charge * b2.charge / distance;
    return direction * forceMagnitude;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Задача N тел");
    window.setFramerateLimit(60);

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::vector<Ball> balls;
    for (int i = 0; i < 10; ++i) {
        float x = std::rand() % static_cast<int>(WIDTH);
        float y = std::rand() % static_cast<int>(HEIGHT);
        float mass = std::rand() % 50 + 10;
        float charge = std::rand() % 2 == 0 ? 10.f : -10.f;
        balls.emplace_back(x, y, mass, charge);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    balls.emplace_back(event.mouseButton.x, event.mouseButton.y, 10.f, -10.f);
                } else if (event.mouseButton.button == sf::Mouse::Right) {
                    balls.emplace_back(event.mouseButton.x, event.mouseButton.y, 100.f, 10.f);
                }
            }
        }

        for (size_t i = 0; i < balls.size(); ++i) {
            sf::Vector2f forceSum = {0.f, 0.f};
            for (size_t j = 0; j < balls.size(); ++j) {
                if (i != j) {
                    sf::Vector2f force = calculateForce(balls[i], balls[j]);
                    forceSum += force / balls[i].mass;
                }
            }
            balls[i].velocity += forceSum * TIME_STEP;
        }

        for (auto& ball : balls) {
            ball.updatePosition();
            ball.checkCollisionWithWalls();
        }

        window.clear(sf::Color::Black);
        for (const auto& ball : balls) {
            window.draw(ball.shape);
        }
        window.display();
    }

    return 0;
}
