#include <stdio.h>
#include <string.h>

void encryptString(char* message, int r, int c, char* encrypted) {
    char matrix[r][c];
    int index = 0;

    // Fill the matrix row-wise
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (index < strlen(message)) {
                matrix[i][j] = message[index++];
            } else {
                matrix[i][j] = ' ';
            }
        }
    }

    // Read the matrix column-wise
    int encryptedIndex = 0;
    for (int j = 0; j < c; ++j) {
        for (int i = 0; i < r; ++i) {
            encrypted[encryptedIndex++] = matrix[i][j];
        }
    }
    encrypted[encryptedIndex] = '\0';
}

int main() {
    char testCases[][20] = {
        "ATTACKATDAWN",
        "HELLO WORLD",
        "ENCRYPTION",
        "SECURITY",
        "PROGRAMMING"
    };
    int rows[] = {3, 3, 3, 3, 3};
    int cols[] = {4, 4, 4, 4, 4};

    for (int i = 0; i < sizeof(testCases) / sizeof(testCases[0]); ++i) {
        char encrypted[100];
        encryptString(testCases[i], rows[i], cols[i], encrypted);
        printf("Original: %s\n", testCases[i]);
        printf("Encrypted: %s\n\n", encrypted);
    }

    return 0;
}