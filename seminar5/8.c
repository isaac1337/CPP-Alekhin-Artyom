#include <stdio.h>
// Тут нужно написать функцию adder

int adder(int a)
{
    static int sum = 0;
    sum += a;
    return sum;
}

int main()
{
    printf("%i\n", adder(10)); // Должен напечатать 10
    printf("%i\n", adder(15)); // Должен напечатать 25
    printf("%i\n", adder(70)); // Должен напечатать 95
}