#include <stdio.h>
#include <math.h>

int solve_quadratic(double a, double b, double c, double* px1, double* px2)
{
    double eps = 1e-10;
    double discriminant = b * b - 4 * a * c;
    if (discriminant < -eps)
        return 0;
    else if (discriminant > eps)
    {
        *px1 = ((-b + sqrt(discriminant)) / (2 * a));
        *px2 = ((-b - sqrt(discriminant) )/ (2 * a));
        
        return 2;
    } 
    else
    {
        *px1 = (-b / (2 * a));

        return 1;
    }
}

int main() {
    double a = 1, b = -5, c = 6; 
    double x1, x2;

    int result = solve_quadratic(a, b, c, &x1, &x2);

    if (result == 0) {
        printf("Корней нет\n");
    } else if (result == 1) {
        printf("Один корень: x1 = %lf\n", x1);
    } else if (result == 2) {
        printf("Два корня: x1 = %lf, x2 = %lf\n", x1, x2);
    }

    return 0;
}