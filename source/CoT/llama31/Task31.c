#include <stdio.h>
#include <string.h>

void dnaComplement(char* dna, char* complement) {
    const char* bases = "ATCG";
    const char* complements = "TAGC";
    int len = strlen(dna);
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (dna[i] == bases[j]) {
                complement[i] = complements[j];
                break;
            }
        }
    }
    complement[len] = '\0';
}

int main() {
    char dna[] = "ATTGC";
    char complement[6];
    dnaComplement(dna, complement);
    printf("%s\n", complement); // TAACG

    strcpy(dna, "GTAT");
    dnaComplement(dna, complement);
    printf("%s\n", complement); // CATA

    strcpy(dna, "ATCG");
    dnaComplement(dna, complement);
    printf("%s\n", complement); // TAGC

    strcpy(dna, "GCTA");
    dnaComplement(dna, complement);
    printf("%s\n", complement); // CGAT

    strcpy(dna, "TCGA");
    dnaComplement(dna, complement);
    printf("%s\n", complement); // AGCT

    return 0;
}