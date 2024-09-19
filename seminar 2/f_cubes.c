#include <stdio.h>

int cube(int a)
{
    return a*a*a;
}

int main()
{
    int b;
    scanf("%i", &b);
    printf("%i\n", cube(b));
}