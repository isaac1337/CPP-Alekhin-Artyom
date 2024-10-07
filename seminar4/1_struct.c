#include <stdio.h>
#include <math.h>

struct point
{
    double x;
    double y;
};
typedef struct point Point;

struct triangle
{
    Point a;
    Point b;
    Point c;
};
typedef struct triangle Triangle;

void print_point(Point d)
{
    printf("(%.2f , %.2f)", d.x, d.y);
    printf("\n");
}

void print_triangle(const Triangle* t)
{
    printf("{");
    print_point(t->a);
    printf(", ");
    print_point(t->b);
    printf(", ");
    print_point(t->c);
    printf("}");
}

double distance(Point a, Point b)
{
    return (sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) ));
}

double get_triangle_perimeter(const Triangle* t)
{
    return distance(t->a, t->b) + distance(t->b, t->c) + distance(t->c, t->a);
}
    


Triangle moved_triangle(const Triangle* t, Point p)
{
    Triangle new_t;
    new_t.a.x = t->a.x + p.x;
    new_t.a.y = t->a.y + p.y;
    new_t.b.x = t->b.x + p.x;
    new_t.b.y = t->b.y + p.y;
    new_t.c.x = t->c.x + p.x;
    new_t.c.y = t->c.y + p.y;
    return new_t; 
}

void move_triangle(Triangle* t, Point p)
{
    (*t).a.x = t->a.x + p.x;
    (*t).a.y = t->a.y + p.y;
    (*t).b.x = t->b.x + p.x;
    (*t).b.y = t->b.y + p.y;
    (*t).c.x = t->c.x + p.x;
    (*t).c.y = t->c.y + p.y;
}
int main()
{
    Triangle t = {{1.00, 0.00}, {0.50, 2.00}, {0.00, 1.50}};
    printf("Perimeter = %.2f\n", get_triangle_perimeter(&t));
    Point d = {1.0, 1.0};
    print_triangle(&t);
    move_triangle(&t, d);
    print_triangle(&t);
}