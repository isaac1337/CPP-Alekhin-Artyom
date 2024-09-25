#include <stdio.h>
#include <math.h>

void circles(double x1, double y1, double r1, double x2, double y2, double r2) {
    double eps = 1e-5;
    
    double distance = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));

    if (fabs((r1 + r2) - distance) < eps) {
        printf("Touch\n");
    } else if ((r1 + r2) - distance < 0) {
        printf("Do not intersect\n");
    } else {
        printf("Intersect\n");
    }
}

int main() 
{
    double x1, y1, r1, x2, y2, r2;

    scanf("%lf %lf %lf", &x1, &y1, &r1);
    scanf("%lf %lf %lf", &x2, &y2, &r2);

    circles(x1, y1, r1, x2, y2, r2);
    return 0;
}