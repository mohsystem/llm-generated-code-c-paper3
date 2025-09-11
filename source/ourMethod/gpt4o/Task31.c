#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* complementDNA(const char* dna) {
    size_t length = strlen(dna);
    char* complement = (char*)malloc(length + 1);
    if (!complement) return NULL;  // Check for memory allocation failure

    for (size_t i = 0; i < length; ++i) {
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
                free(complement);
                fprintf(stderr, "Invalid DNA nucleotide\n");
                return NULL;
        }
    }
    complement[length] = '\0';
    return complement;
}

int main() {
    const char* test_cases[] = {"ATTGC", "GTAT", "AAAA", "CGCG", "ATCG"};
    for (int i = 0; i < 5; ++i) {
        char* result = complementDNA(test_cases[i]);
        if (result) {
            printf("%s -> %s\n", test_cases[i], result);
            free(result);
        }
    }
    return 0;
}