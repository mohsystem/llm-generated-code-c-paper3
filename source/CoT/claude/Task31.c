
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* makeComplement(const char* dna) {
    if(dna == NULL) {
        return NULL;
    }
    
    size_t len = strlen(dna);
    char* result = (char*)malloc(len + 1);
    
    if(result == NULL) {
        return NULL;
    }
    
    for(size_t i = 0; i < len; i++) {
        switch(dna[i]) {
            case 'A': result[i] = 'T'; break;
            case 'T': result[i] = 'A'; break;
            case 'C': result[i] = 'G'; break;
            case 'G': result[i] = 'C'; break;
            default: result[i] = dna[i];
        }
    }
    result[len] = '\\0';
    return result;
}

int main() {
    // Test cases
    char* result;
    
    result = makeComplement("ATTGC");
    printf("%s\\n", result); // Should print: TAACG
    free(result);
    
    result = makeComplement("GTAT");
    printf("%s\\n", result); // Should print: CATA
    free(result);
    
    result = makeComplement("AAAA");
    printf("%s\\n", result); // Should print: TTTT
    free(result);
    
    result = makeComplement("GCGC");
    printf("%s\\n", result); // Should print: CGCG
    free(result);
    
    result = makeComplement("TATA");
    printf("%s\\n", result); // Should print: ATAT
    free(result);
    
    return 0;
}
