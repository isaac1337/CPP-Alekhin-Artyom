#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct book {
    char title[50];
    int pages;
    float price;
};

void print_book(struct book *b) {
    printf("Book info:\n");
    printf("Title: %s\nPages: %d\nPrice: %g\n\n", b->title, b->pages, b->price);
}

typedef struct book Book;

int main() {
    Book* p = (Book*)malloc(sizeof(Book));
    if (p == NULL) {
        printf("Error! Out of memory.\n");
        exit(1);
    }
    strcpy(p->title, "Don Quixote");
    p->pages = 1000;
    p->price = 750.0;

    print_book(p);
    free(p);
    return 0;
}

