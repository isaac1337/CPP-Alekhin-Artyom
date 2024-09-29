#include <stdio.h>

void safe_strcpy(char* dest, size_t dest_size, const char* src)
{
    size_t i;
    for (i = 0; i < dest_size; i++)
    {
        dest[i] = src[i];
    }
    dest[i] = '\0';
}

int main() 
{
    char a[10] = "Mouse";
    char b[50] = "LargeElephant";

    safe_strcpy(a, sizeof(a), b);
    printf("a: %s\n", a); 

    return 0;
}