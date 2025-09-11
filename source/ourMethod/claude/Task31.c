
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* makeComplement(const char* dna) {
    if (dna == NULL) {
        return NULL;
    }
    
    size_t len = strlen(dna);
    if (len == 0) {
        char* empty = (char*)malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\\0';
        return empty;
    }
    
    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i < len; i++) {
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
                return NULL;
        }
    }
    result[len] = '\\0';
    
    return result;
}

int main() {
    // Test cases
    const char* test_cases[] = {
        "ATTGC",  // Expected: TAACG
        "GTAT",   // Expected: CATA
        "AAAA",   // Expected: TTTT
        "GCGC",   // Expected: CGCG
        "ATCG"    // Expected: TAGC
    };
    
    for (int i = 0; i < 5; i++) {
        char* result = makeComplement(test_cases[i]);
        if (result != NULL) {
            printf("Input: %s -> Output: %s\\n", test_cases[i], result);
            free(result);
        } else {
            printf("Error processing input: %s\\n", test_cases[i]);
        }
    }
    
    return 0;
}
