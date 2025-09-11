
#include <stdio.h>

struct BitFields {
    unsigned int field1 : 5;  // 5 bits
    unsigned int field2 : 6;  // 6 bits
    unsigned int field3 : 5;  // 5 bits
};

void setField1(struct BitFields* bf, unsigned int value) {
    bf->field1 = value;
}

void setField2(struct BitFields* bf, unsigned int value) {
    bf->field2 = value;
}

void setField3(struct BitFields* bf, unsigned int value) {
    bf->field3 = value;
}

unsigned int getField1(struct BitFields* bf) {
    return bf->field1;
}

unsigned int getField2(struct BitFields* bf) {
    return bf->field2;
}

unsigned int getField3(struct BitFields* bf) {
    return bf->field3;
}

int main() {
    struct BitFields bf = {0, 0, 0};
    
    // Test case 1
    setField1(&bf, 15);
    setField2(&bf, 35);
    setField3(&bf, 20);
    printf("Test 1: %u %u %u\\n", getField1(&bf), getField2(&bf), getField3(&bf));

    // Test case 2
    setField1(&bf, 31);
    setField2(&bf, 63);
    setField3(&bf, 31);
    printf("Test 2: %u %u %u\\n", getField1(&bf), getField2(&bf), getField3(&bf));

    // Test case 3
    setField1(&bf, 0);
    setField2(&bf, 0);
    setField3(&bf, 0);
    printf("Test 3: %u %u %u\\n", getField1(&bf), getField2(&bf), getField3(&bf));

    // Test case 4
    setField1(&bf, 7);
    setField2(&bf, 42);
    setField3(&bf, 12);
    printf("Test 4: %u %u %u\\n", getField1(&bf), getField2(&bf), getField3(&bf));

    // Test case 5
    setField1(&bf, 25);
    setField2(&bf, 55);
    setField3(&bf, 28);
    printf("Test 5: %u %u %u\\n", getField1(&bf), getField2(&bf), getField3(&bf));

    return 0;
}
