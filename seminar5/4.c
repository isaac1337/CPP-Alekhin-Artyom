#include <stdio.h>
#include <stdlib.h>
#include <math.h>
float* get_geometric_progression(float a, float r, int n)
{
    float* progression = (float*)malloc(n * sizeof(float));
    for (int i = 0; i < n; i++)
    {
        progression[i] = a * pow(r, i);
    }
    
    return progression;
}

int main()
{
    float a = 1;
    float r = 3;
    int n = 10;
    float* progression = get_geometric_progression(a, r, n);
    for (int i = 0; i < n; i++)
    {
        printf("%.1f ", progression[i]);
    }
    free(progression);
}