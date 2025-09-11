
#include <stdio.h>
#include <stdbool.h>

struct BitFields {
    unsigned int flag1 : 1;
    unsigned int flag2 : 1;
    unsigned int value : 6;
};

void setFlag1(struct BitFields* bits, bool value) {
    bits->flag1 = value;
}

void setFlag2(struct BitFields* bits, bool value) {
    bits->flag2 = value;
}

void setValue(struct BitFields* bits, unsigned int val) {
    bits->value = val & 0x3F;  // Ensure only 6 bits are used
}

bool getFlag1(const struct BitFields* bits) {
    return bits->flag1;
}

bool getFlag2(const struct BitFields* bits) {
    return bits->flag2;
}

unsigned int getValue(const struct BitFields* bits) {
    return bits->value;
}

int main() {
    struct BitFields bits = {0, 0, 0};
    
    // Test case 1
    setFlag1(&bits, true);
    setFlag2(&bits, false);
    setValue(&bits, 15);
    printf("Test 1: %d %d %u\\n", getFlag1(&bits), getFlag2(&bits), getValue(&bits));
    
    // Test case 2
    setFlag1(&bits, false);
    setFlag2(&bits, true);
    setValue(&bits, 30);
    printf("Test 2: %d %d %u\\n", getFlag1(&bits), getFlag2(&bits), getValue(&bits));
    
    // Test case 3
    setFlag1(&bits, true);
    setFlag2(&bits, true);
    setValue(&bits, 63);
    printf("Test 3: %d %d %u\\n", getFlag1(&bits), getFlag2(&bits), getValue(&bits));
    
    // Test case 4
    setFlag1(&bits, false);
    setFlag2(&bits, false);
    setValue(&bits, 0);
    printf("Test 4: %d %d %u\\n", getFlag1(&bits), getFlag2(&bits), getValue(&bits));
    
    // Test case 5
    setFlag1(&bits, true);
    setFlag2(&bits, false);
    setValue(&bits, 45);
    printf("Test 5: %d %d %u\\n", getFlag1(&bits), getFlag2(&bits), getValue(&bits));
    
    return 0;
}
