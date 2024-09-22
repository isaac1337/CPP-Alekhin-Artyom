#include <stdio.h>

void alice(int n);
void bob(int n);

void alice(int n) 
{
if (n != 1)
{
    n = 3*n + 1;
    printf("Alice: %1i\n", n);
    bob(n);
}
if (n == 1)
    printf("Alice: %1i\n", n);
}

void bob(int n)
{
if (n != 1)
{
    while (n % 2 == 0)
    {
        n /= 2;
        printf("Bob: %3i\n", n);
    }
    alice(n);
}
if (n == 1)
    printf("Bob: %3i\n", n);
}

int main()
{
    int n;
    scanf("%i", &n);
    alice(n);
    
    return 0;
}