#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getComplementaryDNA(const char* dna, char* complementary) {
    if (dna == NULL || *dna == '\0') {
        fprintf(stderr, "DNA strand cannot be empty or null\n");
        exit(EXIT_FAILURE);
    }
    size_t len = strlen(dna);
    for (size_t i = 0; i < len; ++i) {
        switch (dna[i]) {
            case 'A':
                complementary[i] = 'T';
                break;
            case 'T':
                complementary[i] = 'A';
                break;
            case 'C':
                complementary[i] = 'G';
                break;
            case 'G':
                complementary[i] = 'C';
                break;
            default:
                fprintf(stderr, "Invalid DNA nucleotide: %c\n", dna[i]);
                exit(EXIT_FAILURE);
        }
    }
    complementary[len] = '\0'; // Null terminate the string
}

int main() {
    const char* testCases[] = {"ATTGC", "GTAT", "ATCG", "GCTA", "TCGA"};
    for (size_t i = 0; i < sizeof(testCases) / sizeof(testCases[0]); ++i) {
        size_t len = strlen(testCases[i]);
        char* complementary = malloc((len + 1) * sizeof(char));
        if (complementary == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        getComplementaryDNA(testCases[i], complementary);
        printf("Input: %s -> Output: %s\n", testCases[i], complementary);
        free(complementary);
    }
    return 0;
}