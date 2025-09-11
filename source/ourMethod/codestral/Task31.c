#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* dnaComplement(const char* dna) {
    size_t length = strlen(dna);
    char* result = (char*)malloc(length + 1);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < length; i++) {
        switch (dna[i]) {
            case 'A':
                result[i] = 'T';
                break;
            case 'T':
                result[i] = 'A';
                break;
            case 'C':
                result[i] = 'G';
                break;
            case 'G':
                result[i] = 'C';
                break;
            default:
                fprintf(stderr, "Invalid DNA base: %c\n", dna[i]);
                free(result);
                exit(EXIT_FAILURE);
        }
    }
    result[length] = '\0';
    return result;
}

int main() {
    char* complement = dnaComplement("ATTGC");
    printf("%s\n", complement);  // Output: TAACG
    free(complement);

    complement = dnaComplement("GTAT");
    printf("%s\n", complement);  // Output: CATA
    free(complement);

    return 0;
}