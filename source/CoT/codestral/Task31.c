#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* dnaComplement(const char* dna) {
    int len = strlen(dna);
    char* result = malloc(len + 1);
    if (result == NULL) {
        exit(1);
    }
    for (int i = 0; i < len; i++) {
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
                free(result);
                exit(1);
        }
    }
    result[len] = '\0';
    return result;
}

int main() {
    char* result = dnaComplement("ATTGC");
    printf("%s\n", result); // "TAACG"
    free(result);

    result = dnaComplement("GTAT");
    printf("%s\n", result); // "CATA"
    free(result);

    return 0;
}