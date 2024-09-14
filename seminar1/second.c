#include <stdio.h>
#include <stdbool.h>

int main()
{
    int a, b, c;
    bool cons;
    scanf("%i%i%i", &a, &b, &c);
    if (abs(a-b) == 1 && abs(b-c) == 1)
       cons = true;
    else
       cons = false;
    if ((a>b && b>c) && (cons == true))
       printf("Consecutive Decreasing\n");
    else if ((a>b && b>c) && (cons == false))
       printf("Decreasing\n");
    else if ((a<b && b<c) && (cons == true))
       printf("Consecutive Increasing\n");
    else if ((a<b && b<c) && (cons == false))
       printf("Increasing\n");
    else if (a == b && b == c)
       printf("Equal\n");
    else
       printf("None");
}
    
    
