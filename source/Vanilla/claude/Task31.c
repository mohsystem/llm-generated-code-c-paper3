
#include <stdio.h>
#include <string.h>

char* makeComplement(char* dna) {
    int len = strlen(dna);
    for(int i = 0; i < len; i++) {
        switch(dna[i]) {
            case 'A': dna[i] = 'T'; break;
            case 'T': dna[i] = 'A'; break;
            case 'C': dna[i] = 'G'; break;
            case 'G': dna[i] = 'C'; break;
        }
    }
    return dna;
}

int main() {
    char dna1[] = "ATTGC";
    char dna2[] = "GTAT";
    char dna3[] = "AAAA";
    char dna4[] = "GCGC";
    char dna5[] = "ATCG";
    
    printf("%s\\n", makeComplement(dna1)); // Should print: TAACG
    printf("%s\\n", makeComplement(dna2)); // Should print: CATA
    printf("%s\\n", makeComplement(dna3)); // Should print: TTTT
    printf("%s\\n", makeComplement(dna4)); // Should print: CGCG
    printf("%s\\n", makeComplement(dna5)); // Should print: TAGC
    
    return 0;
}
