#include <stdio.h>
#include <stdlib.h>  
#include <string.h>

#define MAX_GAMES 100
#define MAX_TITLE_LENGTH 50

struct game
{
    char title[MAX_TITLE_LENGTH];
    double avg_rating;
};

typedef struct game Game;

int cmp(const void* a, const void* b)
{
    const Game *gameA = (const Game*)a;
    const Game *gameB = (const Game*)b;
    if (gameB->avg_rating > gameA->avg_rating)
        return 1;
    else if (gameB->avg_rating < gameA->avg_rating)
        return -1;
    else
        return 0;
}

int main() 
{
    char temp;
    int n;
    scanf("%d", &n);
    scanf("%c", &temp);
    Game games[MAX_GAMES];
    for (int i = 0; i < n; i++)
    {
        char title[MAX_TITLE_LENGTH];
        scanf("%[^:]", title);
        scanf("%c", &temp);
        int k;
        scanf("%d", &k);
        int sum = 0;
        for (int j = 0; j < k; j++) 
        {
            int rating;
            scanf("%d", &rating);
            sum += rating;
        }
        double avg = (double)sum / k;

        strcpy(games[i].title, title);
        games[i].avg_rating = avg;
        scanf("%c", &temp); 
        while (temp != '\n' && temp != EOF) 
        {
            scanf("%c", &temp);
        }
    }
    qsort(games, n, sizeof(Game), cmp);
    for (int i = 0; i < n; i++) 
    {
        printf("%s: %.2lf\n", games[i].title, games[i].avg_rating);
    }
}