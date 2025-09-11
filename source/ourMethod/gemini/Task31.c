#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* makeComplement(const char* dna) {
    size_t len = strlen(dna);
    char* complement = (char*)malloc((len + 1) * sizeof(char));
    if (complement == NULL) {
        return NULL; // Handle memory allocation failure
    }
    for (size_t i = 0; i < len; i++) {
        switch (dna[i]) {
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
                free(complement);  // Free allocated memory in case of error
                return NULL;       // Return NULL to indicate error
        }
    }
    complement[len] = '\0';
    return complement;
}

int main() {
    const char* testCases[] = {"ATTGC", "GTAT", "A", "CG", "ATCGTA"};
    const char* expectedOutputs[] = {"TAACG", "CATA", "T", "GC", "TAGCAT"};

    for (int i = 0; i < 5; i++) {
        char* result = makeComplement(testCases[i]);
        if (result != NULL) {
            printf("Input: %s, Output: %s, Expected: %s, Result: %s\n", testCases[i], result, expectedOutputs[i], strcmp(result, expectedOutputs[i]) == 0 ? "true" : "false");
            free(result); // Free the allocated memory
        } else {
            printf("Memory allocation failed or invalid input for test case: %s\n", testCases[i]);
        }
    }
    return 0;
}