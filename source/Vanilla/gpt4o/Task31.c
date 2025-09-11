#include <stdio.h>
#include <string.h>

char* DNAStrand(const char* dna) {
    static char complementaryStrand[100];
    int i;
    for (i = 0; dna[i] != '\0'; ++i) {
        switch (dna[i]) {
            case 'A':
                complementaryStrand[i] = 'T';
                break;
            case 'T':
                complementaryStrand[i] = 'A';
                break;
            case 'C':
                complementaryStrand[i] = 'G';
                break;
            case 'G':
                complementaryStrand[i] = 'C';
                break;
        }
    }
    complementaryStrand[i] = '\0';
    return complementaryStrand;
}

int main() {
    printf("%s\n", DNAStrand("ATTGC")); // Output: "TAACG"
    printf("%s\n", DNAStrand("GTAT"));  // Output: "CATA"
    printf("%s\n", DNAStrand("AGTC"));  // Output: "TCAG"
    printf("%s\n", DNAStrand("AAAA"));  // Output: "TTTT"
    printf("%s\n", DNAStrand("CGCG"));  // Output: "GCGC"
    return 0;
}