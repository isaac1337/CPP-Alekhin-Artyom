#include <stdio.h>

// Это происходит из-за того что в int есть ограничение по диапозону допустимых значений. После 12 они превышены. 
long long fact(int n)
{
    long long result = 1;
    for (int i = 1; i <= n; ++i)
    result *= i;
    return result;
}

int main()
{
    int k;
    scanf("%lli", &k);
    printf("%lli", fact(k));
}
