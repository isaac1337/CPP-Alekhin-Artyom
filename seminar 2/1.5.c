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

    int len = 0;
    for (int j = 0; j < n; ++j)
    {
        if (a[j] >= 0)
        {
            a[len++] = a[j];
        }
    }
    for (int i = 0; i < len ; ++i)
    {
        printf("%i ", a[i]);
    }
}