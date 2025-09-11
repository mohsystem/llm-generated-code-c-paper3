
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 1024
#define MAX_ARRAY_SIZE 100

typedef struct {
    char string_data[MAX_STRING_LENGTH];
    int int_array[MAX_ARRAY_SIZE];
    size_t array_size;
    int is_valid;
} DeserializedData;

// Calculate checksum for verification
uint32_t calculate_checksum(const char* data, size_t length) {
    uint32_t checksum = 0;
    for (size_t i = 0; i < length; i++) {
        checksum = (checksum << 1) ^ (uint32_t)data[i];
    }
    return checksum;
}

// Secure deserialization function
DeserializedData deserialize(const unsigned char* data, size_t data_length) {
    DeserializedData result = {0};
    result.is_valid = 0;

    // Check for minimum data length
    if (data == NULL || data_length < sizeof(uint32_t) + 8) {
        return result;
    }

    // Verify checksum
    uint32_t stored_checksum;
    memcpy(&stored_checksum, data, sizeof(uint32_t));
    
    uint32_t calculated_checksum = calculate_checksum(
        (const char*)(data + sizeof(uint32_t)), 
        data_length - sizeof(uint32_t)
    );

    if (stored_checksum != calculated_checksum) {
        return result;
    }

    // Start parsing after checksum
    const unsigned char* current = data + sizeof(uint32_t);
    size_t remaining = data_length - sizeof(uint32_t);

    // Read string length
    size_t string_length;
    if (remaining < sizeof(size_t)) {
        return result;
    }
    memcpy(&string_length, current, sizeof(size_t));
    current += sizeof(size_t);
    remaining -= sizeof(size_t);

    // Validate string length
    if (string_length >= MAX_STRING_LENGTH || string_length > remaining) {
        return result;
    }

    // Read string
    memcpy(result.string_data, current, string_length);
    result.string_data[string_length] = '\\0';
    current += string_length;
    remaining -= string_length;

    // Read array size
    if (remaining < sizeof(size_t)) {
        return result;
    }
    memcpy(&result.array_size, current, sizeof(size_t));
    current += sizeof(size_t);
    remaining -= sizeof(size_t);

    // Validate array size
    if (result.array_size > MAX_ARRAY_SIZE || 
        remaining < result.array_size * sizeof(int)) {
        return result;
    }

    // Read array elements
    memcpy(result.int_array, current, result.array', type='text')