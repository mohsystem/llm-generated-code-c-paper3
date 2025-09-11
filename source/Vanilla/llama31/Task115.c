#include <stdio.h>

struct BitFields {
    unsigned int bit0 : 1;
    unsigned int bit1to3 : 3;
    unsigned int bit4 : 1;
    unsigned int bit5 : 1;
    unsigned int bit6to7 : 2;
};

int main() {
    struct BitFields bitFields;
    bitFields.bit0 = 1;
    bitFields.bit1to3 = 5;
    bitFields.bit4 = 1;
    bitFields.bit5 = 0;
    bitFields.bit6to7 = 2;

    printf("Bit 0: %d\n", bitFields.bit0);
    printf("Bits 1-3: %d\n", bitFields.bit1to3);
    printf("Bit 4: %d\n", bitFields.bit4);
    printf("Bit 5: %d\n", bitFields.bit5);
    printf("Bits 6-7: %d\n", bitFields.bit6to7);

    return 0;
}