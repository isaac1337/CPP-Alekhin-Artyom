#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct book
{
    char title[50];
    int pages;
    float price;
};

void print_book(struct book b)
{
    printf("Book info:\n");
    printf("Title: %s\nPages: %d\nPrice: %g\n\n", b.title, b.pages, b.price);
}

typedef struct book Book;

int main()
{
    Book greatbook;
    Book* book = &greatbook;
    strcpy(book->title, "Don Quixote");
    book->pages = 1000;
    book->price = 750.0;

    print_book(*book);
}

