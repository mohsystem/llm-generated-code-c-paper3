
#include <stdio.h>
#include <stdlib.h>

struct BitFields {
    unsigned int field1 : 3;  // 3 bits for values 0-7
    unsigned int field2 : 4;  // 4 bits for values 0-15
    unsigned int field3 : 5;  // 5 bits for values 0-31
};

void setBitFields(struct BitFields* bf, unsigned int f1, unsigned int f2, unsigned int f3) {
    if (f1 > 7 || f2 > 15 || f3 > 31) {
        printf("Error: Invalid input values\\n");
        return;
    }
    
    bf->field1 = f1;
    bf->field2 = f2;
    bf->field3 = f3;
}

void printBitFields(const struct BitFields* bf) {
    printf("%u %u %u\\n", bf->field1, bf->field2, bf->field3);
}

int main() {
    struct BitFields bf;
    
    // Test case 1
    printf("Test1: ");
    setBitFields(&bf, 3, 7, 15);
    printBitFields(&bf);
    
    // Test case 2
    printf("Test2: ");
    setBitFields(&bf, 5, 10, 20);
    printBitFields(&bf);
    
    // Test case 3
    printf("Test3: ");
    setBitFields(&bf, 0, 0, 0);
    printBitFields(&bf);
    
    // Test case 4
    printf("Test4: ");
    setBitFields(&bf, 7, 15, 31);
    printBitFields(&bf);
    
    // Test case 5
    printf("Test5: ");
    setBitFields(&bf, 1, 8, 16);
    printBitFields(&bf);
    
    return 0;
}
