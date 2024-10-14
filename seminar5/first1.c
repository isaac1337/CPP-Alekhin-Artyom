#include <stdio.h>
#include <stdlib.h>

int main()
{
    size_t* p = (size_t*)malloc(sizeof(size_t));
    if (p == NULL)
    {
        printf("Error! Out of memory.\n");
        exit(1);
    }
    *p = 123;
    printf("%zu\n", *p);

    free(p);
    return 0;
}