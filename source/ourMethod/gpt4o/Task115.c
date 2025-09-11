#include <stdio.h>

struct BitFieldStruct {
    unsigned int bitField1 : 1;
    unsigned int bitField2 : 3;
    unsigned int bitField3 : 4;
};

int main() {
    struct BitFieldStruct b1 = {1 & 0x1, 5 & 0x7, 10 & 0xF};
    struct BitFieldStruct b2 = {0 & 0x1, 3 & 0x7, 7 & 0xF};
    struct BitFieldStruct b3 = {1 & 0x1, 7 & 0x7, 15 & 0xF};
    struct BitFieldStruct b4 = {0 & 0x1, 0 & 0x7, 0 & 0xF};
    struct BitFieldStruct b5 = {1 & 0x1, 2 & 0x7, 4 & 0xF};

    printf("%u, %u, %u\n", b1.bitField1, b1.bitField2, b1.bitField3);
    printf("%u, %u, %u\n", b2.bitField1, b2.bitField2, b2.bitField3);
    printf("%u, %u, %u\n", b3.bitField1, b3.bitField2, b3.bitField3);
    printf("%u, %u, %u\n", b4.bitField1, b4.bitField2, b4.bitField3);
    printf("%u, %u, %u\n", b5.bitField1, b5.bitField2, b5.bitField3);

    return 0;
}