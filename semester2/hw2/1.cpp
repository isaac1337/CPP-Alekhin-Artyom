#include <iostream>
#include <cmath>
using std::cout, std::endl;

/*
    Вспомогательная структура Vector2f, которая описывает математический вектор в двумерном пространстве.
    Также написаны функции для удобной работы с этой структурой.
    Работает примерно также, как и класс sf::Vector2f из библиотеки SFML.
    (но подключать целую библиотеку только ради класса sf::Vector2f не стоит)
*/

struct Vector2f
{
    float x, y;
};

Vector2f operator+(Vector2f left, Vector2f right)
{
    Vector2f result = {left.x + right.x, left.y + right.y};
    return result;
}

Vector2f operator*(Vector2f left, float right)
{
    Vector2f result = {left.x * right, left.y * right};
    return result;
}

Vector2f operator*(float left, Vector2f right)
{
    Vector2f result = {left * right.x, left * right.y};
    return result;
}

Vector2f& operator+=(Vector2f& left, Vector2f right)
{
    left.x += right.x;
    left.y += right.y;
    return left;
}

float getDistance(Vector2f a, Vector2f b)
{
    return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

std::ostream& operator<<(std::ostream& out, Vector2f right)
{
    out << "(" << right.x << ", " << right.y << ")";
    return out;
}

/*
    Базовый класс Shape, который содержит общие поля и методы для всех фигур.
*/

class Shape
{
protected:
    Vector2f mPosition;

public:
    Shape() : mPosition({0, 0}) {}

    Vector2f getPosition()
    {
        return mPosition;
    }

    void setPosition(Vector2f newPosition)
    {
        mPosition = newPosition;
    }

    void move(Vector2f change)
    {
        mPosition += change;
    }

    virtual float calculatePerimeter() = 0; // Чисто виртуальная функция
};

/*
    Классы Circle, Rectangle и Triangle, которые наследуются от Shape.
*/

class Circle : public Shape
{
private:
    float mRadius;

public:
    Circle(float radius) : mRadius(radius) {}

    float calculatePerimeter() override
    {
        return 2 * M_PI * mRadius;
    }
};

class Rectangle : public Shape
{
private:
    float mWidth;
    float mHeight;

public:
    Rectangle(float width, float height) : mWidth(width), mHeight(height) {}

    float calculatePerimeter() override
    {
        return 2 * (mWidth + mHeight);
    }
};

class Triangle : public Shape
{
private:
    Vector2f mPointA;
    Vector2f mPointB;
    Vector2f mPointC;

public:
    Triangle(Vector2f pointA, Vector2f pointB, Vector2f pointC) : mPointA(pointA), mPointB(pointB), mPointC(pointC) {}

    float calculatePerimeter() override
    {
        return getDistance(mPointA, mPointB) + getDistance(mPointB, mPointC) + getDistance(mPointC, mPointA);
    }
};

int main()
{
    Circle a(10);
    cout << "Circle perimeter: " << a.calculatePerimeter() << endl;
    a.move({5, 5});
    cout << "Circle position after move: " << a.getPosition() << endl;

    Rectangle b(100, 200);
    cout << "Rectangle perimeter: " << b.calculatePerimeter() << endl;
    b.move({-10, 20});
    cout << "Rectangle position after move: " << b.getPosition() << endl;

    Triangle c({5, 2}, {-7, 5}, {4, 4});
    cout << "Triangle perimeter: " << c.calculatePerimeter() << endl;
    c.move({3, -3});
    cout << "Triangle position after move: " << c.getPosition() << endl;
}
