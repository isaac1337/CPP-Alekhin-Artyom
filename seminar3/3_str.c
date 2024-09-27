#include <stdio.h>

char is_palindrom(char *str)
{
    int i = 0, counter = 0;
    while (str[i] != '\0')
    {
        counter += 1;
        i += 1;
    }
    for (int i = 0; i < (counter / 2 ); ++i)
    {
        if (str[i] == str[counter-1-i])
        {
            continue;
        }
        else
        {
            return 0;
        }
    }
        return 1;
}

int main()
{
    char str[100];
    scanf("%s", str);
    if (is_palindrom(str))
    {
        printf("Yes");
    }
    else
    {
        printf("No");
    }
}