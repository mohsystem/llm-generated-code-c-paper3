#include <stdio.h>
#include <math.h>
#include <string.h>

void encryption(char* s, char* encrypted) {
    int l = strlen(s);
    int b = (int) ceil(sqrt(l));
    int a = (int) floor(sqrt(l));
    if (b * a < l) {
        if (b < a) {
            b = b + 1;
        } else {
            a = a + 1;
        }
    }
    char arr[a][b];
    memset(arr, ' ', sizeof(arr));
    int k = 0;
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            if (k < l) {
                arr[i][j] = s[k];
                k++;
            }
        }
    }
    k = 0;
    for (int j = 0; j < b; j++) {
        for (int i = 0; i < a; i++) {
            encrypted[k++] = arr[i][j];
        }
    }
    encrypted[k] = '\0';
}

void decryption(char* s, char* decrypted) {
    int l = strlen(s);
    int b = (int) ceil(sqrt(l));
    int a = (int) floor(sqrt(l));
    if (b * a < l) {
        if (b < a) {
            b = b + 1;
        } else {
            a = a + 1;
        }
    }
    char arr[a][b];
    memset(arr, ' ', sizeof(arr));
    int k = 0;
    for (int j = 0; j < b; j++) {
        for (int i = 0; i < a; i++) {
            if (k < l) {
                arr[i][j] = s[k];
                k++;
            }
        }
    }
    k = 0;
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            decrypted[k++] = arr[i][j];
        }
    }
    decrypted[k] = '\0';
}

int main() {
    char testCases[][100] = {"hello", "world", "encryption", "decryption", "testcase"};
    char encrypted[100], decrypted[100];
    for (int i = 0; i < 5; i++) {
        encryption(testCases[i], encrypted);
        decryption(encrypted, decrypted);
        printf("Original: %s\n", testCases[i]);
        printf("Encrypted: %s\n", encrypted);
        printf("Decrypted: %s\n\n", decrypted);
    }
    return 0;
}