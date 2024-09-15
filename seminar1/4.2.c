#include <stdio.h>
#include <limits.h>

int main()
{
    int n;
    scanf("%i", &n);
    int even_max = INT_MIN;
    int noteven_max = INT_MIN;
    
    for (int i = 0; i < n; ++i)
    {
        int a;
        scanf("%i", &a);
        if ((a % 2 == 0) && (a > even_max))
            even_max = a;
        else if (a > noteven_max)
            noteven_max = a;
    }

    if (even_max == INT_MIN)
        printf("None ");
    else
        printf("%i ", even_max);

    if (noteven_max == INT_MIN)
        printf("None");
    else
        printf("%i", noteven_max);
}

