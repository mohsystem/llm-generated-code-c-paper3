#include <stdio.h>

struct Data {
    unsigned int bitField : 4; // Ensure only 4 bits are used
};

void setBitField(struct Data *data, unsigned int field) {
    data->bitField = field & 0xF;
}

unsigned int getBitField(const struct Data *data) {
    return data->bitField;
}

int main() {
    struct Data testCases[] = {
        {0},
        {1},
        {15},
        {16},
        {255}
    };

    for (int i = 0; i < 5; i++) {
        printf("Bit Field: %u\n", getBitField(&testCases[i]));
    }

    return 0;
}