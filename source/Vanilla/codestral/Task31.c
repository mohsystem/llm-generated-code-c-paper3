#include <stdio.h>
#include <string.h>

void makeComplement(const char* dna, char* result) {
    for (int i = 0; i < strlen(dna); i++) {
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
        }
    }
    result[strlen(dna)] = '\0';
}

int main() {
    char result[6];
    makeComplement("ATTGC", result);
    printf("%s\n", result); // TAACG
    makeComplement("GTAT", result);
    printf("%s\n", result); // CATA
    return 0;
}