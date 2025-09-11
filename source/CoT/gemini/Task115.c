#include <stdio.h>

struct BitFields {
    unsigned int a : 2;
    unsigned int b : 4;
    unsigned int c : 2;
};

int main() {
    struct BitFields bf1;
    bf1.a = 3;
    bf1.b = 10;
    bf1.c = 1;
    printf("Test case 1: a=%u, b=%u, c=%u\n", bf1.a, bf1.b, bf1.c);

    struct BitFields bf2;
    bf2.a = 0;
    bf2.b = 15;
    bf2.c = 3;
    printf("Test case 2: a=%u, b=%u, c=%u\n", bf2.a, bf2.b, bf2.c);

    struct BitFields bf3;
    bf3.a = -1;
    bf3.b = -1;
    bf3.c = -1;
    printf("Test case 3: a=%u, b=%u, c=%u\n", bf3.a, bf3.b, bf3.c);

    struct BitFields bf4;
    bf4.a = 1;
    bf4.b = 0;
    bf4.c = 2;
    printf("Test case 4: a=%u, b=%u, c=%u\n", bf4.a, bf4.b, bf4.c);

    struct BitFields bf5;
    bf5.a = 2;
    bf5.b = 8;
    bf5.c = 0;
    printf("Test case 5: a=%u, b=%u, c=%u\n", bf5.a, bf5.b, bf5.c);

    return 0;
}