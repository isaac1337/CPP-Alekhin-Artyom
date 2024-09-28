#include <stdio.h>

void trim_after_first_space(char str[])
{
    int i = 0;
    while (str[i] != ' ')
    {
        i++;
    }
    str[i] = '\0';
}
int main()
{
char a[] = "Cats and Dogs";
printf("%s\n", a); // Должно напечатать Cats and Dogs
trim_after_first_space(a);
printf("%s\n", a); // Должно напечатать Cats
}
