#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() 
{
    char** p = (char**)malloc(sizeof(char*));
    if (p == NULL)
    {
        printf("Error! Out of memory.\n");
        exit(1);
    }

    *p = (char *)malloc(13 * sizeof(char)); 
    if (*p == NULL) 
    {
        printf("Error! Out of memory.\n");
        exit(1);
    }

    strcpy(*p, "Cats and Dogs"); 
    printf("%s\n", *p);

    free(*p); 
    free(p); 
    return 0;
}
