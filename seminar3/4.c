#include <stdio.h>
#include <math.h>

float pi_calc(int n)
{
    float result = 0;
    for (int i = 0; i < n; ++i)
    {
        result += (float) 4 * ((i % 2 == 0 ? 1 : -1)) / (2*i + 1);
    }
    
    return result;
}

int main()
{
    int n;
    scanf("%i", &n);
    printf("%f\n", pi_calc(n));
}
