#include <stdio.h>
#include <limits.h>

int main()
{
    int a, b, counter = 1, max_number, max_counter = INT_MIN;
    scanf("%i %i", &a, &b);
    for (int i = a; i<=b; ++i)
    {
        counter = 1;
        int j = i;
        while (j != 1)
        {
            if (j % 2 == 0)
            {
                j /= 2;
                counter += 1;
            }
            else
            {
                j = 3*j +1;
                counter += 1;
             } 
        }
        if (counter > max_counter)
        {
            max_counter = counter;
            max_number = i;
        }
    }
    printf("\nNumber = %i Counter = %i", max_number, max_counter);
}