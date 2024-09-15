#include <stdio.h>
#include <limits.h>
int main()
{
    int n;
    scanf("%i", &n);
    
    int first, second;
    int is_increasing = 1;
    int is_decreasing = 1;
    int is_equal = 1;
    
    scanf("%i", &first);
    for (int i = 0; i < n-1; ++i)
    {
        scanf("%i", &second);
        if (second > first)
        {
            is_decreasing = 0;
            is_equal = 0;
        }
        if (second < first)
        {
            is_increasing = 0;
            is_equal = 0;
        }
        if (second == first)
        {
            is_increasing = 0;
            is_decreasing = 0;
        }
        
        first = second;
    }

    if (is_increasing) 
    {
        printf("Increasing\n");
    } 
    else if (is_decreasing) 
    {
        printf("Decreasing\n");
    } 
    else if (is_equal)
    {
        printf("Equal\n");
    } 
    else 
    {
         printf("None\n");
    }
}