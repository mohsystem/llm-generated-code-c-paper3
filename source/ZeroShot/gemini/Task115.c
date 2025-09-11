#include <stdio.h>
#include <string.h>

struct PackedData {
    unsigned int val1 : 4;
    unsigned int val2 : 6;
    unsigned int val3 : 8;
};


char* packData(int v1, int v2, int v3) {
    struct PackedData data;
    data.val1 = v1;
    data.val2 = v2;
    data.val3 = v3;

    static char buffer[100]; // Ensure sufficient size
    snprintf(buffer, sizeof(buffer), "val1: %u, val2: %u, val3: %u", data.val1, data.val2, data.val3);
    return buffer;
}

int main() {
    printf("%s\n", packData(1, 2, 3));
    printf("%s\n", packData(15, 63, 255));
    printf("%s\n", packData(0, 0, 0));
    printf("%s\n", packData(7, 31, 127));
    printf("%s\n", packData(-1, -1, -1)); // Demonstrates wrapping behavior
    return 0;
}