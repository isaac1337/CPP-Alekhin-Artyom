#include <stdio.h>
#include <limits.h>

int main()
{
    int a, counter = 1, max = INT_MIN;
    scanf("%i", &a);
    while (a != 1)
    {
        if (a % 2 == 0)
        {
            if (a > max)
            {
                max = a;
            }
            a /= 2;
            printf("%i ", a);
            counter += 1;
        }
        else
        {
            if (a > max)
            {
                max = a;
            }            
            a = 3*a +1;
            printf("%i ", a);
            counter += 1;
        }
    }
    printf("\nLenght = %i Max = %i", counter, max);
}