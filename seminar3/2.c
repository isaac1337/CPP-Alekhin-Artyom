#include <stdio.h>


long long int partial_permutation(int n, int k)
{
    long long int result = 1; 
    for (int i = 0; i < k; ++i)
    {
        result *= (n-i);
    }
    return result;
}

int main()
{
    int n, k;
    scanf("%i %i", &n, &k);
    printf("%lli\n", partial_permutation(n, k));
}
