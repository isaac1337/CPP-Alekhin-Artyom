#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void encryptChar(char* ch, int k) {
    if (*ch >= 'a' && *ch <= 'z') {
        *ch = (*ch - 'a' + k) % 26 + 'a';
    }
    else if (*ch >= 'A' && *ch <= 'Z') {
        *ch = (*ch - 'A' + k) % 26 + 'A';
    }
}

int main(int argc, char* argv[]) 
{

    const char* input_filename = argv[1];
    const char* output_filename = argv[2];
    int key = atoi(argv[3]);

    FILE* input_file = fopen(input_filename, "r");
    FILE* output_file = fopen(output_filename, "w");

    char ch;
    while ((ch = fgetc(input_file)) != EOF) {
        encryptChar(&ch, key);
        fputc(ch, output_file);
    }

    fclose(input_file);
    fclose(output_file);

    return 0;
}
