#include <stdio.h>

struct BitFieldStruct {
    unsigned int a : 1;
    unsigned int b : 1;
    unsigned int c : 2;
};

int main() {
    struct BitFieldStruct bf;
    bf.a = 1;
    bf.b = 0;
    bf.c = 2;

    printf("Test Case 1: a = %d, b = %d, c = %d\n", bf.a, bf.b, bf.c);

    bf.a = 0;
    bf.b = 1;
    bf.c = 1;
    printf("Test Case 2: a = %d, b = %d, c = %d\n", bf.a, bf.b, bf.c);

    bf.a = 1;
    bf.b = 1;
    bf.c = 0;
    printf("Test Case 3: a = %d, b = %d, c = %d\n", bf.a, bf.b, bf.c);

    bf.a = 0;
    bf.b = 0;
    bf.c = 3;
    printf("Test Case 4: a = %d, b = %d, c = %d\n", bf.a, bf.b, bf.c);

    bf.a = 1;
    bf.b = 1;
    bf.c = 3;
    printf("Test Case 5: a = %d, b = %d, c = %d\n", bf.a, bf.b, bf.c);

    return 0;
}