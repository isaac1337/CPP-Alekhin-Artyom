#include <stdio.h>

float yearfrac(int year, int day)
{
    if (year % 4 == 0)
    {
        return (float) day / 366;
    }
    else
    {
        return (float) day / 365;
    }
}

int main()
{
    int y, d;
    scanf("%i %i", &y, &d);
    printf("%.5f", yearfrac(y, d));
}
