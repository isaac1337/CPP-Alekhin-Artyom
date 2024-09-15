#include <stdio.h>
#include <limits.h>
int main()
{
    int n;
    int k;
    scanf("%i", &n);
    int max = INT_MIN;
    for (int i = 0; i < n; ++i)
    {
        int a;
        scanf("%i", &a);
        if (a > max)
        {
            max = a;
            k = 1;
        }
        else if (a == max)
        {
            k = k + 1;
        }
    }
    printf("%i %i", max, k);
}
