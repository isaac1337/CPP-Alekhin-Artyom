#include <stdio.h>

void encrypt(char* str, int k)
{
    char ch;
    int i = 0;
    while (str[i] != '\0')
    {
    ch = str[i];
        if (ch >= 'a' && ch <= 'z')
        {
            ch = (ch - 'a' + k) % 26 + 'a';
        } 
        else if (ch >= 'A' && ch <= 'Z')
        {
            ch = (ch - 'A' + k) % 26 + 'A';
        }
        
        str[i] = ch;
        i++;
    }
}

int main()
{
    char str[100];
    int k;
    scanf("%i %[^\n]", &k, str);
    encrypt(str, k);
    printf("%s\n", str);
}