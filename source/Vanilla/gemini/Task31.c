#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* makeComplement(const char* dna) {
    size_t len = strlen(dna);
    char* complement = (char*)malloc((len + 1) * sizeof(char));
    if (complement == NULL) {
        return NULL; 
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
        }
    }
    complement[len] = '\0';
    return complement;
}

int main() {
    char* result1 = makeComplement("ATTGC");
    printf("%s\n", result1);
    free(result1);

    char* result2 = makeComplement("GTAT");
    printf("%s\n", result2);
    free(result2);
    
    char* result3 = makeComplement("AAAA");
    printf("%s\n", result3);
    free(result3);

    char* result4 = makeComplement("TTTT");
    printf("%s\n", result4);
    free(result4);
    
    char* result5 = makeComplement("CGCG");
    printf("%s\n", result5);
    free(result5);

    return 0;
}