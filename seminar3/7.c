#include <stdio.h>

int main() {
    printf("Размер 'char': %zu байт\n", sizeof(char));
    printf("Размер 'short': %zu байт\n", sizeof(short));
    printf("Размер 'int': %zu байт\n", sizeof(int));
    printf("Размер 'long long': %zu байт\n", sizeof(long long));
    printf("Размер 'size_t': %zu байт\n", sizeof(size_t));
    printf("Размер 'float': %zu байт\n", sizeof(float));
    printf("Размер 'double': %zu байт\n", sizeof(double));
    printf("Размер 'int[10]': %zu байт\n", sizeof(int[10]));
    printf("Размер 'char[10]': %zu байт\n", sizeof(char[10]));

    return 0;
}