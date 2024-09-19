#include <stdio.h>

int main()
{
    int n;
    scanf("%i", &n);
    int a[100][100], b[100][100], c[100][100]; 
    
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            scanf("%d", &a[i][j]);
        }
    }   
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            scanf("%d", &b[i][j]);
        }
    }
    
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j)
        {
            c[i][j] = 0;
            for (int k = 0; k < n; ++k)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    
    for(int i = 0; i < n; i++) 
    {
        for(int j = 0; j < n; j++) 
        {
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
}