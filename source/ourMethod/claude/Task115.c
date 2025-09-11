
#include <stdio.h>
#include <stdlib.h>

struct BitFields {
    unsigned int field1 : 3;  // 3 bits for values 0-7
    unsigned int field2 : 4;  // 4 bits for values 0-15
};

// Function to safely set field1
void setField1(struct BitFields* bf, unsigned int value) {
    if (bf == NULL) {
        fprintf(stderr, "Error: NULL pointer\\n");
        exit(1);
    }
    if (value > 7) {
        fprintf(stderr, "Error: Field1 must be between 0 and 7\\n");
        exit(1);
    }
    bf->field1 = value;
}

// Function to safely set field2
void setField2(struct BitFields* bf, unsigned int value) {
    if (bf == NULL) {
        fprintf(stderr, "Error: NULL pointer\\n");
        exit(1);
    }
    if (value > 15) {
        fprintf(stderr, "Error: Field2 must be between 0 and 15\\n");
        exit(1);
    }
    bf->field2 = value;
}

// Function to safely get field1
unsigned int getField1(const struct BitFields* bf) {
    if (bf == NULL) {
        fprintf(stderr, "Error: NULL pointer\\n");
        exit(1);
    }
    return bf->field1;
}

// Function to safely get field2
unsigned int getField2(const struct BitFields* bf) {
    if (bf == NULL) {
        fprintf(stderr, "Error: NULL pointer\\n");
        exit(1);
    }
    return bf->field2;
}

int main() {
    struct BitFields bf = {0, 0};  // Initialize all fields to 0
    
    // Test case 1: Set and get field1
    setField1(&bf, 5);
    printf("Field1: %u\\n", getField1(&bf));
    
    // Test case 2: Set and get field2
    setField2(&bf, 10);
    printf("Field2: %u\\n", getField2(&bf));
    
    // Test case 3: Set both fields
    setField1(&bf, 3);
    setField2(&bf, 12);
    printf("Field1: %u, Field2: %u\\n", getField1(&bf), getField2(&bf));
    
    // Test case 4: Set field1 to max value
    setField1(&bf, 7);
    printf("Field1 max: %u\\n", getField1(&bf));
    
    // Test case 5: Set field2 to max value
    setField2(&bf, 15);
    printf("Field2 max: %u\\n", getField2(&bf));
    
    return 0;
}
