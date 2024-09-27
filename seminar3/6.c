#include <stdio.h>
#include <math.h>

const double step = 1e-2; 
const double eps = 1e-10; 
// цикл завершаю не только когда area < eps, а еще когда t > t_peak. Если не было бы этого условия, цикл завершался бы слишком рано и не успел досчитать до соответствующего значения. Максимум функции при x-1, далее она стремится к 0. Поэтому беру значения несколько больше максимума, дальше пренебрегаю
double gamma(double x) {
    double integrand(double t, double x) {
        return pow(t, x - 1) * exp(-t);
    }

    double total_area = 0;
    double t = 0;
    double t_peak = x - 1;
    while (1) 
    {
        double area = 0.5 * step * (integrand(t, x) + integrand(t + step, x));
        total_area += area;
        t += step;
        if (t > t_peak && area < eps) 
            break;
    }

    return total_area;
}

int main() {
    double x;
    printf("Введите значение x (> 1): ");
    scanf("%lf", &x);
    if (gamma(x) > 1e6)
    {
        printf("Значение гамма-функции в точке %.2f равно %.5e\n", x, gamma(x));
    }
    else
    {
        printf("Значение гамма-функции в точке %.2f равно %.4f\n", x, gamma(x));

    }
    return 0;
}
