#include <iostream>
#include <cmath>
#include <numbers>
using std::cout, std::endl;

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
};

class Circle : public Shape
{
private:
    float mRadius;
public:
    Circle(float radius) : mRadius(radius) { }

    float calculatePerimeter()
    {
        return 2 * std::numbers::pi * mRadius;
    }
};

class Rectangle : public Shape
{
private:
    float mWidth;
    float mHeight;
public:
    Rectangle(float width, float height) : mWidth(width), mHeight(height) { }

    float calculatePerimeter()
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
    Triangle(Vector2f pointA, Vector2f pointB, Vector2f pointC) : 
             mPointA(pointA), mPointB(pointB), mPointC(pointC)
    {
    }

    float calculatePerimeter()
    {
        return getDistance(mPointA, mPointB) + getDistance(mPointB, mPointC) + getDistance(mPointC, mPointA);
    }
};

int main()
{
    Circle a(10);
    cout << "Circle perimeter: " << a.calculatePerimeter() << endl;
    cout << "Initial Circle position: " << a.getPosition() << endl;
    a.move({5, 5});
    cout << "Circle new position: " << a.getPosition() << endl;

    Rectangle b(100, 200);
    cout << "\nRectangle perimeter: " << b.calculatePerimeter() << endl;
    cout << "Initial Rectangle position: " << b.getPosition() << endl;
    b.move({-10, 15});
    cout << "Rectangle new position: " << b.getPosition() << endl;

    Triangle c({5, 2}, {-7, 5}, {4, 4});
    cout << "\nTriangle perimeter: " << c.calculatePerimeter() << endl;
    cout << "Initial Triangle position: " << c.getPosition() << endl;
    c.move({20, 10});
    cout << "Triangle new position: " << c.getPosition() << endl;

    return 0;
}
