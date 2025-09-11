#include <stdio.h>
#include <string.h>

void dnaComplement(char* dna, char* complement) {
    char* mapping[] = {"T", "A", "C", "G"};
    for (int i = 0; i < strlen(dna); i++) {
        switch (dna[i]) {
            case 'A':
                strcat(complement, mapping[0]);
                break;
            case 'T':
                strcat(complement, mapping[1]);
                break;
            case 'G':
                strcat(complement, mapping[2]);
                break;
            case 'C':
                strcat(complement, mapping[3]);
                break;
        }
    }
}

int main() {
    char testCases[][10] = {"ATTGC", "GTAT", "ATCG", "TGCA", "GATTACA"};
    char complement[100];
    for (int i = 0; i < 5; i++) {
        strcpy(complement, "");
        dnaComplement(testCases[i], complement);
        printf("Input: %s Output: %s\n", testCases[i], complement);
    }
    return 0;
}