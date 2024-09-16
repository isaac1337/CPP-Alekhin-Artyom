#include <stdio.h>
int main()
{
    int a[1000];
    int n;
    scanf("%i", &n);
    
    for (int i = 0; i < n; ++i)
    {
        scanf("%i", &a[i]);
    }

    int number, k;
    scanf("%i %i", &number, &k);

    for (int j = n; j > k; --j)
    {
        a[j] = a[j - 1];
    }
    a[k+1] = number;

    for (int i = 0; i < n + 1; ++i)
    {
        printf("%i ", a[i]);
    }
    printf("\n");

    return 0;
}