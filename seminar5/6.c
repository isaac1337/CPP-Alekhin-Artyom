#include <stdio.h>
#include <stdlib.h>
int less(int a, int b);
int greater(int a, int b);
int last_digit_less(int a, int b);

void sort(int* a, size_t n, int (*cmp)(int a, int(b)))
{
    for (size_t j = 0; j < n; ++j)
    {
        size_t target_index = j;
        for (size_t i = j + 1; i < n; ++i)
        {
            if (cmp(a[i], a[target_index]) < 0)
            target_index = i;
        }   

        int temp = a[j];
        a[j] = a[target_index];
        a[target_index] = temp;
    }
}

int less(int a, int b)
{
    return a - b;
}
int greater(int a, int b)
{
    return b - a;
}
int last_digit_less(int a, int b)
{
    return (a % 10) - (b % 10);
}



void print(int* a, size_t n)
{
    for (size_t i = 0; i < 6; ++i)
        printf("%i ", a[i]);
    printf("\n");
}
    // Тут нужно написать новую функцию sort и функции - компараторы:
    // less - сортировка по возрастанию
    // greater - по убыванию
    // last_digit_less - по возрастанию последней цифры
int main()
{
    int a[] = {32, 63, 29, 54, 81};
    sort(a, 5, less);
    print(a, 5); // Должен напечатать 29 32 54 63 81
    sort(a, 5, greater);
    print(a, 5); // Должен напечатать 81 63 54 32 29
    sort(a, 5, last_digit_less);
    print(a, 5); // Должен напечатать 81 32 63 54 29
}