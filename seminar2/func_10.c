#include <stdio.h>

void transpose(float a[][500], int n)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            float temp = a[i][j];
            a[i][j] = a[j][i];
            a[j][i] = temp;
        }
    }
}

void print(float a[][500], int n)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            printf("%f ", a[i][j]);
        }
        printf("\n");
    }
}

int main() 
{
    int n;
    float a[500][500];
    scanf("%i", &n);
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            scanf("%f", &a[i][j]);
        }
    }
    transpose(a, n);
    print(a,n);
}
