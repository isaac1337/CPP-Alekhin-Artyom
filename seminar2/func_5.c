#include <stdio.h>

void print_binary(int a)
{
    if (a > 1)
    {
        print_binary((a / 2));
    }
    
    printf("%i", a % 2);
}

int main() 
{
    int b;
    scanf("%i", &b);
    print_binary(b);
}