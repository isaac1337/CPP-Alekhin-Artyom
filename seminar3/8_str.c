#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    char* str = argv[1];
    int n = atoi(argv[2]);
    for (int i = 0; i < n; ++i)
    {
        printf("%s ", str);
    }
}
