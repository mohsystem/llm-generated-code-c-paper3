#include <stdio.h>
#include <stdint.h>

typedef struct {
    uint32_t flags;
} BitField;

void setFlag(BitField* bitField, int bitPosition, int value) {
    if (value) {
        bitField->flags |= 1 << bitPosition;
    } else {
        bitField->flags &= ~(1 << bitPosition);
    }
}

int getFlag(const BitField* bitField, int bitPosition) {
    return (bitField->flags & (1 << bitPosition)) != 0;
}

int main() {
    BitField bitField;
    bitField.flags = 0;

    setFlag(&bitField, 0, 1);
    setFlag(&bitField, 1, 1);
    setFlag(&bitField, 2, 0);

    printf("Flag 0: %d\n", getFlag(&bitField, 0));
    printf("Flag 1: %d\n", getFlag(&bitField, 1));
    printf("Flag 2: %d\n", getFlag(&bitField, 2));

    return 0;
}