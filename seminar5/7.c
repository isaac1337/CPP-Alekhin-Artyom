#include <stdio.h>
#include <math.h>

int is_negative(int a)
{
    if (a < 0)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}
int is_even(int a)
{
    if (a % 2 == 0)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}
int is_square(int a)
{
    if (a < 0)
    {
        return -1;
    }
    int root = (int)sqrt((double)a);
    if (root * root == a)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}
// Тут нужно написать функцию count_if и функции - предикаты:
// is_negative - проверяет, является ли число отрицательным
// is_even - проверяет, является ли число чётным
// is_square - проверяет, является ли число квадратом целого числа

int count_if(int* a, size_t n, int (*pr)(int))
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if(pr(a[i]) > 0)
        {
            count += 1;
        }
    }
    return count;
}
int main()
{
    int a[] = {89, 81, 28, 52, 44, 16, -64, 49, 52, -79};
    printf("%zu\n", count_if(a, 10, is_negative)); // Должен напечатать 2
    printf("%zu\n", count_if(a, 10, is_even)); // Должен напечатать 6
    printf("%zu\n", count_if(a, 10, is_square)); // Должен напечатать 3
}
