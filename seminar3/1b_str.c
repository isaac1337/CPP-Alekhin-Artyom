#include <stdio.h>

int main() 
{
    char a;
    scanf("%c", &a);

    if ((a >= 'A' && a <= 'Z') || (a >= 'a' && a <= 'z')) 
    {
        printf("Letter\n");
    } else if (a >= '0' && a <= '9') {
        printf("Digit\n");
    } else {
        printf("Other\n");
    }

    return 0;
}