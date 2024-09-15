#include <stdio.h>
#include <math.h>

int main()
{
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    
    for (int i = a; i <= b;)
    {
        if (i % c == 0)
        {
            printf("%i ", i);
            i += c;
        }
        else
        {
           ++i;
        }
    }
}
    