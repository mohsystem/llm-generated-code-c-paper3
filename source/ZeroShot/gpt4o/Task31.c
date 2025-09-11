#include <stdio.h>
#include <string.h>

void dnaComplement(const char *dna, char *complement) {
    for (size_t i = 0; i < strlen(dna); i++) {
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
        }
    }
    complement[strlen(dna)] = '\0';
}

int main() {
    char complement[6];
    dnaComplement("ATTGC", complement);
    printf("%s\n", complement); // TAACG
    dnaComplement("GTAT", complement);
    printf("%s\n", complement); // CATA
    dnaComplement("GCGC", complement);
    printf("%s\n", complement); // CGCG
    dnaComplement("TACG", complement);
    printf("%s\n", complement); // ATGC
    dnaComplement("ATAT", complement);
    printf("%s\n", complement); // TATA
    return 0;
}