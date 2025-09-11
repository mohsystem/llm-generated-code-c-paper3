
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* makeComplement(const char* dna) {
    int len = strlen(dna);
    char* complement = (char*)malloc((len + 1) * sizeof(char));
    
    for(int i = 0; i < len; i++) {
        switch(dna[i]) {
            case 'A': complement[i] = 'T'; break;
            case 'T': complement[i] = 'A'; break;
            case 'C': complement[i] = 'G'; break;
            case 'G': complement[i] = 'C'; break;
        }
    }
    complement[len] = '\\0';
    return complement;
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
    
    result = makeComplement("ATCG");
    printf("%s\\n", result); // Should print: TAGC
    free(result);
    
    return 0;
}
