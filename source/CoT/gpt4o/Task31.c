#include <stdio.h>
#include <string.h>

char* getComplementaryDNA(const char* dna) {
    static char complementary[100];
    int i;
    for (i = 0; dna[i] != '\0'; i++) {
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
        }
    }
    complementary[i] = '\0';
    return complementary;
}

int main() {
    printf("%s\n", getComplementaryDNA("ATTGC")); // Output: TAACG
    printf("%s\n", getComplementaryDNA("GTAT"));  // Output: CATA
    printf("%s\n", getComplementaryDNA("AAAA"));  // Output: TTTT
    printf("%s\n", getComplementaryDNA("CGCG"));  // Output: GCGC
    printf("%s\n", getComplementaryDNA("ATGC"));  // Output: TACG
    return 0;
}