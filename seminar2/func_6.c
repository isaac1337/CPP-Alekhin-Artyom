#include <stdio.h>

int data[1000];

int tribrec(int n)
{
    if (n == 2)
    {
        return 1;
    }
    if (n < 2)
    {
        return 0;
    }
    if (data[n] == 0)
    {
        data[n] = tribrec(n - 1) + tribrec(n - 2) + tribrec(n - 3);
    }

    return data[n];

}
int main()
{
    printf("%i", tribrec(38));
}