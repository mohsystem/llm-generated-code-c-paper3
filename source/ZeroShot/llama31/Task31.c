#include <stdio.h>
#include <string.h>

char* getComplementaryDNA(char* dna) {
    char* complementary = (char*)malloc(strlen(dna) + 1);
    char complements[] = {'T', 'A', 'G', 'C'};
    char nucleotides[] = {'A', 'T', 'C', 'G'};

    for (int i = 0; i < strlen(dna); i++) {
        for (int j = 0; j < 4; j++) {
            if (dna[i] == nucleotides[j]) {
                complementary[i] = complements[j];
                break;
            }
        }
    }
    complementary[strlen(dna)] = '\0';
    return complementary;
}

int main() {
    char* testCases[] = {"ATTGC", "GTAT", "ATCG", "GCTA", "TCGA"};
    for (int i = 0; i < 5; i++) {
        char* result = getComplementaryDNA(testCases[i]);
        printf("%s\n", result);
        free(result);
    }
    return 0;
}