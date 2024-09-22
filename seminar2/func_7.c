#include <stdio.h>

void is_even(int a[], int size)
{
    int even_counter = 0;
    for (int i = 0; i < size; ++i)
    {
        if (a[i] % 2 == 0)
            ++even_counter;
    }
    printf("%i", even_counter);
}

int main() {
    int size, a[500];
    scanf("%i", &size);
    for (int i = 0; i < size; ++i)
        scanf("%i", &a[i]);
    is_even(a, size);

    return 0;
}