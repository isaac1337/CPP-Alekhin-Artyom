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


void bubbleSort_sd(int arr[], int n) 
{
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) 
        {
            if (sum_of_digits(arr[j]) > sum_of_digits(arr[j + 1])) 
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int n;
    int a[10000];
    scanf("%i", &n);
    for(int i = 0; i < n; ++i)
    {
        scanf("%i", &a[i]);
    }
    bubbleSort_sd(a, n);
    for(int i = 0; i < n; ++i)
    {
        printf("%i ", a[i]);
    }
    printf("\n");
}