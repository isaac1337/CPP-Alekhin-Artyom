#include <stdio.h>
#include <string.h>

int main() 
{
    int n, dist, x = 0, y = 0;
    char direction[10];
    scanf("%i", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%s %i", direction, &dist);
        {
            if (strcmp(direction, "North") == 0)
            {
                y += dist;
            }
            else if (strcmp(direction, "South") == 0)
            {
                y -= dist;
            }
            else if (strcmp(direction, "East") == 0)
            {
                x += dist;
            }
            else if (strcmp(direction, "West") == 0)
            {
                x -= dist;
            }
        }
    }
    printf("%i %i", x, y);
}