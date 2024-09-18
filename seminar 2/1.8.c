#include <stdio.h>
int main()
{
    int a[1000], b[1000];
    int n, k;
    scanf("%i", &n);
    for (int i = 0; i < n; ++i)
        scanf("%i", &a[i]);
    scanf("%i", &k);
    for (int i = n; i >= 0; i--)
    {
        b[(i + k) % n] = a[i];
    }
    for (int i = 0; i < n; ++i)
        printf("%i ", b[i]);
        
    printf("\n");
}
