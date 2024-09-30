#include <stdio.h>
#include <string.h>

void swap(char** a, char** b) {
    char* temp = *a;
    *a = *b;
    *b = temp;
}

int main(int argc, char* argv[]) {

    for (int i = 1; i < argc - 1; i++) {
        for (int j = 1; j < argc - i; j++) {
            if (strcmp(argv[j], argv[j + 1]) > 0) {
                swap(&argv[j], &argv[j + 1]);
            }
        }
    }

    for (int i = 1; i < argc; i++) {
        printf("%s\n", argv[i]);
    }

    return 0;
}