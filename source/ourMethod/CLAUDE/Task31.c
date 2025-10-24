#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "../../../../../../../../usr/include/stdint.h"

// Function to return the complementary DNA strand
// Security: Input validation, bounds checking, and safe memory management
// Returns NULL on error (caller must check and free result)
char* getDNAComplement(const char* dna) {
    // Validate input pointer - treat all inputs as untrusted
    if (dna == NULL) {
        return NULL;
    }

    // Get length and validate it's not excessive
    size_t len = strlen(dna);

    // Check for empty string (though problem states DNA is never empty)
    if (len == 0) {
        // Allocate empty string
        char* result = (char*)calloc(1, sizeof(char));
        if (result == NULL) {
            return NULL; // Memory allocation failed
        }
        result[0] = '\0';
        return result;
    }

    // Validate length to prevent excessive memory allocation (DoS prevention)
    const size_t MAX_DNA_LENGTH = 10000000; // 10 million characters
    if (len > MAX_DNA_LENGTH) {
        return NULL; // Length exceeds safe limit
    }

    // Allocate memory for result string (+1 for null terminator)
    // Check for integer overflow in size calculation
    if (len >= SIZE_MAX - 1) {
        return NULL; // Would overflow
    }

    char* complement = (char*)calloc(len + 1, sizeof(char));

    // Check if allocation succeeded
    if (complement == NULL) {
        return NULL; // Memory allocation failed
    }

    // Process each character with bounds checking and validation
    for (size_t i = 0; i < len; i++) {
        // Bounds check: ensure we're within input bounds
        if (i >= len) {
            free(complement);
            return NULL;
        }

        char nucleotide = dna[i];

        // Input validation: only accept valid DNA characters
        // This prevents injection of unexpected characters
        switch (nucleotide) {
            case 'A':
                complement[i] = 'T';
                break;
            case 'T':
                complement[i] = 'A';
                break;
            case 'C':
                complement[i] = 'G';
                break;
            case 'G':
                complement[i] = 'C';
                break;
            default:
                // Invalid character - fail closed
                free(complement);
                return NULL;
        }
    }

    // Ensure null termination (calloc already did this, but being explicit)
    complement[len] = '\0';

    return complement;
}

// Test cases
int main(void) {
    // Test case 1: Standard example from problem
    char* result1 = getDNAComplement("ATTGC");
    if (result1 != NULL) {
        printf("Test 1: ATTGC -> %s (Expected: TAACG)\n", result1);
        free(result1);
        result1 = NULL;
    } else {
        printf("Test 1 failed: NULL returned\n");
    }

    // Test case 2: Standard example from problem
    char* result2 = getDNAComplement("GTAT");
    if (result2 != NULL) {
        printf("Test 2: GTAT -> %s (Expected: CATA)\n", result2);
        free(result2);
        result2 = NULL;
    } else {
        printf("Test 2 failed: NULL returned\n");
    }

    // Test case 3: All A's
    char* result3 = getDNAComplement("AAAA");
    if (result3 != NULL) {
        printf("Test 3: AAAA -> %s (Expected: TTTT)\n", result3);
        free(result3);
        result3 = NULL;
    } else {
        printf("Test 3 failed: NULL returned\n");
    }

    // Test case 4: All combinations
    char* result4 = getDNAComplement("ATCG");
    if (result4 != NULL) {
        printf("Test 4: ATCG -> %s (Expected: TAGC)\n", result4);
        free(result4);
        result4 = NULL;
    } else {
        printf("Test 4 failed: NULL returned\n");
    }

    // Test case 5: Longer sequence
    char* result5 = getDNAComplement("GCGCGCGC");
    if (result5 != NULL) {
        printf("Test 5: GCGCGCGC -> %s (Expected: CGCGCGCG)\n", result5);
        free(result5);
        result5 = NULL;
    } else {
        printf("Test 5 failed: NULL returned\n");
    }

    return 0;
}
