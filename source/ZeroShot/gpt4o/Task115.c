#include <stdio.h>

typedef struct {
    unsigned int field1 : 2;
    unsigned int field2 : 4;
} BitFieldStruct;

void testCases() {
    BitFieldStruct example1 = {2, 5};
    BitFieldStruct example2 = {3, 15};
    BitFieldStruct example3 = {0, 0};
    BitFieldStruct example4 = {1, 8};
    BitFieldStruct example5 = {3, 7};

    printf("Example1: %u, %u\n", example1.field1, example1.field2);
    printf("Example2: %u, %u\n", example2.field1, example2.field2);
    printf("Example3: %u, %u\n", example3.field1, example3.field2);
    printf("Example4: %u, %u\n", example4.field1, example4.field2);
    printf("Example5: %u, %u\n", example5.field1, example5.field2);
}

int main() {
    testCases();
    return 0;
}