#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char* p = (char*)malloc((9 * sizeof(char)));
    if (p == NULL)
    {
        printf("Error! Out of memory.\n");
        exit(1);
    }
    strcpy(p,"Elephant");
    printf("%s\n", p);

    free(p);
    return 0;
}