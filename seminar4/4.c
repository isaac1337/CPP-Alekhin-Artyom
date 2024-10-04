#include <stdio.h>

void first_mult2(int* p, size_t n)
{
    for (size_t i = 0; i < n; ++i)
    {
        *(p+i) *= 2;
    }
}

void second_mult2(int* p, size_t n)
{
    for (size_t i = 0; i < n; ++i) 
    {
        p[i] *= 2;
    }
}
void printArray(int* arr, size_t n) 
{
    for (size_t i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    size_t n = sizeof(arr) / sizeof(arr[0]);


    first_mult2(arr, n);
    printArray(arr, n);

    int arr_b[] = {1, 2, 3, 4, 5};

    second_mult2(arr_b, n);
    printArray(arr_b, n);

    return 0;
}