#include <stdio.h>
int main()
{
    int n, m;
    scanf("%i %i", &n, &m);
    int col_sum[1000] = {0};
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            int elem;
            scanf("%i", &elem);
            col_sum[j] += elem;
        }
    }
    for (int i = 0; i < m; ++i)
        printf("%i ", col_sum[i]);
        
    printf("\n");
}
