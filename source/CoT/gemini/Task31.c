#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* makeComplement(const char* dna) {
    size_t len = strlen(dna);
    char* complement = (char*)malloc(sizeof(char) * (len + 1));
    if (complement == NULL) {
        return NULL; // Handle memory allocation failure
    }

    for (size_t i = 0; i < len; i++) {
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
                // Handle invalid input if needed
                free(complement);
                return NULL; 
        }
    }
    complement[len] = '\0';
    return complement;
}

int main() {
    char* result1 = makeComplement("ATTGC");
    printf("%s\n", result1 ? result1 : "Error"); // Expected: TAACG
    free(result1);

    char* result2 = makeComplement("GTAT");
    printf("%s\n", result2 ? result2 : "Error"); // Expected: CATA
    free(result2);

    char* result3 = makeComplement("AAAA");
    printf("%s\n", result3 ? result3 : "Error"); // Expected: TTTT
    free(result3);
    
    char* result4 = makeComplement("CGCG");
    printf("%s\n", result4 ? result4 : "Error"); // Expected: GCGC
    free(result4);

    char* result5 = makeComplement("ATCG");
    printf("%s\n", result5 ? result5 : "Error"); // Expected: TAGC
    free(result5);
    

    return 0;
}