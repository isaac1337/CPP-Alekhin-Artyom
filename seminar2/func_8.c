#include <stdio.h>

void reverse(int a[], int size) 
{
    int temp;
    int start = 0;
    int end = size - 1;

    while (start < end) 
    {
        temp = a[start];
        a[start] = a[end];
        a[end] = temp;

        start++;
        end--;
    }
}

int main() 
{
    int size, a[500];
    scanf("%i", &size);
    for (int i = 0; i < size; ++i)
        scanf("%i", &a[i]);
    reverse(a, size);

for (int i = 0; i < size; ++i)
        printf("%i ", a[i]);

    return 0;
}