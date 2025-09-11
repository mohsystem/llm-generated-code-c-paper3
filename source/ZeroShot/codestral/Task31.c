#include <stdio.h>
#include <string.h>

char* dnaComplement(const char* dna) {
    static char result[100];
    int i;
    for (i = 0; i < strlen(dna); i++) {
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
    result[i] = '\0';
    return result;
}

int main() {
    printf("%s\n", dnaComplement("ATTGC")); // TAACG
    printf("%s\n", dnaComplement("GTAT")); // CATA
    // Add more test cases here
    return 0;
}