#include <stdio.h>

struct BitField {
    unsigned int a : 2;
    unsigned int b : 4;
    unsigned int c : 2;
};

int main() {
    struct BitField bf1 = {1, 5, 3};
    struct BitField bf2 = {0, 15, 0};
    struct BitField bf3 = {3, 0, 1};
    struct BitField bf4 = {2, 10, 2};
    struct BitField bf5 = {1, 8, 3};

    printf("a=%u, b=%u, c=%u\n", bf1.a, bf1.b, bf1.c);
    printf("a=%u, b=%u, c=%u\n", bf2.a, bf2.b, bf2.c);
    printf("a=%u, b=%u, c=%u\n", bf3.a, bf3.b, bf3.c);
    printf("a=%u, b=%u, c=%u\n", bf4.a, bf4.b, bf4.c);
    printf("a=%u, b=%u, c=%u\n", bf5.a, bf5.b, bf5.c);

    return 0;
}