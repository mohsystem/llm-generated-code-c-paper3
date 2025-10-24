#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Given one side of a DNA strand, this function returns the other complementary side.
 * 'A' and 'T' are complements of each other, as are 'C' and 'G'.
 * 
 * @param dna A constant pointer to a null-terminated string representing one side of the DNA.
 * @return A pointer to a newly allocated string containing the complement.
 *         The caller is responsible for freeing this memory using free().
 *         Returns NULL if the input is NULL or if memory allocation fails.
 */
char* make_complement(const char* dna) {
    if (dna == NULL) {
        return NULL;
    }

    size_t len = strlen(dna);
    char* complement = (char*)malloc(len + 1);
    
    if (complement == NULL) {
        perror("Failed to allocate memory");
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
            default:
                // For robustness, copy unexpected characters as they are.
                complement[i] = dna[i];
                break;
        }
    }
    
    complement[len] = '\0';
    
    return complement;
}

void run_test(const char* input, const char* expected, int test_num) {
    char* result = make_complement(input);
    
    printf("Test Case %d:\n", test_num);
    printf("Input:    %s\n", input);
    
    if (result != NULL) {
        printf("Output:   %s\n", result);
        printf("Expected: %s\n", expected);
        printf("Result:   %s\n", strcmp(result, expected) == 0 ? "Passed" : "Failed");
        free(result); // Free the allocated memory
    } else {
        printf("Output:   (null)\n");
        printf("Result:   Failed (Memory allocation error or null input)\n");
    }
    
    printf("--------------------\n");
}

int main() {
    const char* test_inputs[] = {"ATTGC", "GTAT", "AAAA", "GCGC", "GATTACA"};
    const char* expected_outputs[] = {"TAACG", "CATA", "TTTT", "CGCG", "CTAATGT"};
    int num_tests = sizeof(test_inputs) / sizeof(test_inputs[0]);

    for (int i = 0; i < num_tests; i++) {
        run_test(test_inputs[i], expected_outputs[i], i + 1);
    }

    return 0;
}