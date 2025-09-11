#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define NAME_LENGTH 5
#define UPPERCASE_LETTERS "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define NUM_OF_LETTERS 26
#define NUM_OF_DIGITS 10

bool usedNames[NUM_OF_LETTERS * NUM_OF_LETTERS * NUM_OF_DIGITS * NUM_OF_DIGITS * NUM_OF_DIGITS] = {false};

char generateRandomChar() {
    return UPPERCASE_LETTERS[rand() % NUM_OF_LETTERS];
}

char generateRandomDigit() {
    return '0' + (rand() % NUM_OF_DIGITS);
}

void generateName(char *name) {
    name[0] = generateRandomChar();
    name[1] = generateRandomChar();
    name[2] = generateRandomDigit();
    name[3] = generateRandomDigit();
    name[4] = generateRandomDigit();
    name[5] = '\0';
}

bool isNameUsed(char *name) {
    int index = (name[0] - 'A') * NUM_OF_LETTERS * NUM_OF_DIGITS * NUM_OF_DIGITS * NUM_OF_DIGITS +
                (name[1] - 'A') * NUM_OF_DIGITS * NUM_OF_DIGITS * NUM_OF_DIGITS +
                (name[2] - '0') * NUM_OF_DIGITS * NUM_OF_DIGITS +
                (name[3] - '0') * NUM_OF_DIGITS +
                (name[4] - '0');
    return usedNames[index];
}

void markNameAsUsed(char *name) {
    int index = (name[0] - 'A') * NUM_OF_LETTERS * NUM_OF_DIGITS * NUM_OF_DIGITS * NUM_OF_DIGITS +
                (name[1] - 'A') * NUM_OF_DIGITS * NUM_OF_DIGITS * NUM_OF_DIGITS +
                (name[2] - '0') * NUM_OF_DIGITS * NUM_OF_DIGITS +
                (name[3] - '0') * NUM_OF_DIGITS +
                (name[4] - '0');
    usedNames[index] = true;
}

void resetName(char *name) {
    int index = (name[0] - 'A') * NUM_OF_LETTERS * NUM_OF_DIGITS * NUM_OF_DIGITS * NUM_OF_DIGITS +
                (name[1] - 'A') * NUM_OF_DIGITS * NUM_OF_DIGITS * NUM_OF_DIGITS +
                (name[2] - '0') * NUM_OF_DIGITS * NUM_OF_DIGITS +
                (name[3] - '0') * NUM_OF_DIGITS +
                (name[4] - '0');
    usedNames[index] = false;
}

char* generateUniqueName() {
    char *name = malloc(sizeof(char) * (NAME_LENGTH + 1));
    do {
        generateName(name);
    } while (isNameUsed(name));
    markNameAsUsed(name);
    return name;
}

int main() {
    srand(time(0));
    char *name1 = generateUniqueName();
    char *name2 = generateUniqueName();
    char *name3 = generateUniqueName();
    printf("%s\n", name1);  // Test case 1
    printf("%s\n", name2);  // Test case 2
    printf("%s\n", name3);  // Test case 3
    resetName(name3);
    char *name4 = generateUniqueName();
    char *name5 = generateUniqueName();
    printf("%s\n", name4);  // Test case 4 (should be different from name3)
    printf("%s\n", name5);  // Test case 5
    free(name1);
    free(name2);
    free(name3);
    free(name4);
    free(name5);
    return 0;
}