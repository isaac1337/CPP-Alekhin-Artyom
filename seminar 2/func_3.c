    #include <stdio.h>
    
    void print_even(int a, int b)
    {
        if (a % 2 == 0)
        {
            for (int i = a; i <= b; i += 2)
            {
                printf("%i ", i);
            }
        }
        else
        {
        for (int i = a + 1; i <= b; i += 2)
            {
                printf("%i ", i);
            }
        }
    }
    
    int main()
    {
        int a, b;
        scanf("%i %i", &a, &b);
        print_even(a, b);
    }