#include <stdio.h>

void cube(float* px)
{
    *px = *px * *px * *px;
}

int main()
{
    float res = 3;
    cube(&res);
    printf("%f\n", res);
}