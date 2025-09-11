#include <stdint.h>

// Defining a struct with bit fields in C
typedef struct {
    uint8_t field1 : 3;
    uint8_t field2 : 5;
} BitFieldStruct;