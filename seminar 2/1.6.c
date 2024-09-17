#include <stdio.h>

int main()
{
    int a[1000];
    int n;
    scanf("%i", &n);
    for (int i = 0; i < n; ++i)
        scanf("%i", &a[i]);
    int o_ind = 0;
    
    for (int i = 0; i < n; ++i)
    {
        if (a[i] % 2 != 0)
        {
            int now = a[o_ind];
            a[o_ind] = a[i];
            a[i] = now;
            ++o_ind;
        }
    }
    for (int i = 0; i < n; ++i)
        
        printf("%i ", a[i]);
        
    printf("\n");
}
