#include <stdio.h>

int sum_of_digits(int a)
{
    int sum = 0;
    while (a > 0)
    {
        sum += a % 10;
        a = a / 10;
    }
    return sum;
}

int sum_of_digits_rec(int a)
{
    if (a != 0)
    {
        return a % 10 + sum_of_digits_rec(a / 10);
    }
    else
    {
        return 0;
    }
}

int main() 
{
    int b;
    scanf("%i", &b);
    int result = sum_of_digits(b);
    int result_rec = sum_of_digits_rec(b);
    printf("%i %i", result, result_rec);
}