#include <iostream>
#include "point.hpp"
using std::cout, std::endl;

class Circle
{
private:
	Point center;
	float radius;

public:
    Circle()
        :center(Point(0,0)), radius(1.0f)
    {
    }
    Circle(const Point& center, float radius)
    {
        this->center = center;
        this->radius = radius;
    }
    Circle(const Circle& circle)
    {
        this->center = circle.center;
        this->radius = circle.radius;
    }
    Point getCenter() const
    {
        return center;
    }
    float getRadius() const
    {
        return radius;
    }

    void newradius(float r)
    {
        if (r > 0)
        {
            radius = r;
        }
        else
        {
            radius = 0;
        }
    }
    void newcenter(const Point& newCenter)
    {
        center = newCenter;
    }

    float area() const
    {
        return radius * radius * 3.14f;
    }

    float distance(const Point& p)
    {
        return std::sqrt((p.x -center.x) * (p.x - center.x) + (p.y - center.y) * (p.y - center.y)) - radius;
    } 
    bool isColliding(const Circle& c) const
    {
        float centerDistance = center.distance(c.getCenter());
        return centerDistance <= (radius + c.getRadius());
    }
    void move(const Point& p)
    {
        center.x += p.x;
        center.y += p.y;
    }

};

int main()
{
	Point p = {7, -1};
	Point q = {-4, 2};
	cout << "p = " << p << endl;
	cout << "q = " << q << endl;
	cout << "p + q = " << p + q << endl;


	Circle a({4, 1}, 3);
	Circle b;

	cout << "Circle a: center: " << a.getCenter() << " radius: " << a.getRadius() << endl; 
	cout << "Circle b: center: " << b.getCenter() << " radius: " << b.getRadius() << endl;

	cout << "Area of a = " << a.area() << endl;
	cout << "Distance from point p to circle a = " << a.distance(p) << endl;


	cout << "Collisions:" << endl;
	if (a.isColliding(b))
		cout << "Yes, a is colliding b" << endl;
	else
		cout << "No, a isn't colliding b" << endl;


	cout << "Moving b by {1, 1}:" << endl;
	b.move({1, 1});
	if (a.isColliding(b))
		cout << "Yes, a is colliding b" << endl;
	else
		cout << "No, a isn't colliding b" << endl;

}