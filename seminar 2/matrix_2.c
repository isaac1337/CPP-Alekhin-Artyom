// Online C compiler to run C program online
#include <stdio.h>
void bubble_sort(int a[][1000], int n, int m)
{
    for (int col = 0; col < m; col++)
    {
        for (int j = 0; j < n; ++j)
        {
            for (int i = 0; i < n - 1 - j; i += 1)
            {
                if (a[i][col] > a[i + 1][col])
                {
                    int temp = a[i][col];
                    a[i][col] = a[i + 1][col];
                    a[i + 1][col] = temp;
                }
            }
        }
    }
}
int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    int a[1000][1000]; 
    
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < m; ++j) 
        {
            scanf("%d", &a[i][j]);
        }
    }   
    
    bubble_sort(a, n, m);
    for(int i = 0; i < n; i++) 
    {
        for(int j = 0; j < m; j++) 
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }    
}