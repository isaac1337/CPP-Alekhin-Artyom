#include <stdio.h>
int main()
{
    int a[1000];
    int n;
    scanf("%i", &n);
    for (int i = 0; i < n; ++i)
        scanf("%i", &a[i]);
    for (int i = n; i >= 0; i--)
    {
        a[2*i] = a[i];
        a[2*i+1] = a[i];
    }
    for (int i = 0; i < 2*n; ++i)
        printf("%i ", a[i]);
        
    printf("\n");
}
