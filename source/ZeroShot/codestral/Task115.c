#include <stdbool.h>

struct BitFields {
    bool bit1:1;
    bool bit2:1;
    int bit3:3;
    bool bit4:1;
};

int main() {
    struct BitFields bitFields;
    // Test cases
    bitFields.bit1 = true;
    bitFields.bit2 = false;
    bitFields.bit3 = 3;
    bitFields.bit4 = true;
    // More test cases can be added here
    return 0;
}