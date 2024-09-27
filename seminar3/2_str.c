#include <stdio.h>

int main() 
{
    char str1[100];
    char str2[100];
    char str[200];
    scanf("%s %s", str1, str2);
    int i = 0, j = 0, k = 0;
    while (str1[i] != '\0' && str2[j] != '\0')
    {
        str[k++] = str1[i++];
        str[k++] = str2[j++];
    }
    while (str1[i] != '\0')
    {
       str[k++] = str1[i++]; 
    }
    while (str2[j] != '\0')
    {
       str[k++] = str2[j++]; 
    }
    printf("%s\n", str);
}