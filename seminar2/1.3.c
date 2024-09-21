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

    int k;
    scanf("%i", &k);
    for (int j = k; j != n-1; ++j)
    {
        a[j] = a[j+1];
    }
 
    for (int i = 0; i < n-1 ; ++i)
    {
        printf("%i ", a[i]);
    }
    printf("\n");

    return 0;
}