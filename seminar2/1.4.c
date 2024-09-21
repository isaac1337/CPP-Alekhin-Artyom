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

    int f, s, counter = 0;
    scanf("%i %i", &f, &s);
    for (int j = f; j != n-(s-f); ++j)
    {
        a[j] = a[s+counter];
        ++counter;
    }
 
    for (int i = 0; i < n-(s-f) ; ++i)
    {
        printf("%i ", a[i]);
    }
    printf("\n");

    return 0;
}