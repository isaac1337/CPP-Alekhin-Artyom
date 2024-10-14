#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct book {
    char* title;
    int pages;
    float price;
};

void print_book(struct book b) {
    printf("Book info:\n");
    printf("Title: %s\nPages: %d\nPrice: %g\n\n", b.title, b.pages, b.price);
}

typedef struct book Book;

struct library {
    Book* books;
    int number_of_books;
};
typedef struct library Library;

Library library_create(int number_of_books) {
    Library lib;
    lib.number_of_books = number_of_books;
    lib.books = (Book*)malloc(number_of_books * sizeof(Book));
    if (lib.books == NULL) {
        printf("Error! Out of memory.\n");
        exit(1);
    }
    return lib;
}

void library_set(Library lib, int index, const char* title, int pages, float price) {
    lib.books[index].title = (char*)malloc(strlen(title) + 1);
    strcpy(lib.books[index].title, title);
    lib.books[index].price = price;
    lib.books[index].pages = pages;
}

Book library_get(Library lib, int index) {
    return lib.books[index]; 
}

void library_print(Library lib) {
    for(int i = 0; i < lib.number_of_books; i++) {
        printf("Book %d info:\n", i + 1);
        printf("Title: %s\nPages: %i\nPrice: %g\n", lib.books[i].title, lib.books[i].pages, lib.books[i].price);
    }
}

void library_destroy(Library lib) {
    for(int i = 0; i < lib.number_of_books; i++) {
        free(lib.books[i].title);
    }
    free(lib.books); 
}

int main() {
    Library a = library_create(3);

    library_set(a, 0, "Don Quixote", 1000, 750.0);
    library_set(a, 1, "Oblomov", 400, 250.0);
    library_set(a, 2, "The Odyssey", 500, 500.0);

    library_print(a);

    print_book(library_get(a, 1));

    library_destroy(a);

    return 0;
}
