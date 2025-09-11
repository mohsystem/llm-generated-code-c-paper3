#include <stdio.h>

typedef struct {
    int bitField;
} Task115;

// Set bit at position pos to 1
void setBit(Task115 *bitField, int pos) {
    bitField->bitField |= (1 << pos);
}

// Set bit at position pos to 0
void clearBit(Task115 *bitField, int pos) {
    bitField->bitField &= ~(1 << pos);
}

// Get the bit at position pos
int getBit(Task115 *bitField, int pos) {
    return (bitField->bitField & (1 << pos)) != 0 ? 1 : 0;
}

int main() {
    Task115 bitField = {0};
    setBit(&bitField, 3);
    printf("%d\n", getBit(&bitField, 3)); // prints 1
    clearBit(&bitField, 3);
    printf("%d\n", getBit(&bitField, 3)); // prints 0
    return 0;
}