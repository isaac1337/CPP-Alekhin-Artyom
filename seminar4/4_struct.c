#include <stdio.h>


struct cat {
    char x;
    size_t y;
};

struct dog {
    size_t y;
    char x;
};

struct mouse {
    char x;
    char y;
    size_t z;
};

struct rat {
    char x;
    size_t z;
    char y;
};

struct fox {
    char x;
    struct mouse y;
};

int main(void) {
    printf("1. char:\n");
    printf("   size: %zu bytes\n", sizeof(char));
    printf("   alignment: %zu bytes\n\n", _Alignof(char));

    printf("2. int:\n");
    printf("   size: %zu bytes\n", sizeof(int));
    printf("   alignment: %zu bytes\n\n", _Alignof(int));

    printf("3. size_t:\n");
    printf("   size: %zu bytes\n", sizeof(size_t));
    printf("   alignment: %zu bytes\n\n", _Alignof(size_t));

    printf("4. int[10]:\n");
    printf("   size: %zu bytes\n", sizeof(int[10]));
    printf("   alignment: %zu bytes\n\n", _Alignof(int[10]));

    printf("5. int*:\n");
    printf("   size: %zu bytes\n", sizeof(int *));
    printf("   alignment: %zu bytes\n\n", _Alignof(int *));

    printf("6. struct cat:\n");
    printf("   size: %zu bytes\n", sizeof(struct cat));
    printf("   alignment: %zu bytes\n\n", _Alignof(struct cat));

    printf("7. struct dog:\n");
    printf("   size: %zu bytes\n", sizeof(struct dog));
    printf("   alignment: %zu bytes\n\n", _Alignof(struct dog));

    printf("8. struct mouse:\n");
    printf("   size: %zu bytes\n", sizeof(struct mouse));
    printf("   alignment: %zu bytes\n\n", _Alignof(struct mouse));

    printf("9. struct rat:\n");
    printf("   size: %zu bytes\n", sizeof(struct rat));
    printf("   alignment: %zu bytes\n\n", _Alignof(struct rat));

    printf("10. struct fox:\n");
    printf("    size: %zu bytes\n", sizeof(struct fox));
    printf("    alignment: %zu bytes\n\n", _Alignof(struct fox));

    return 0;
}