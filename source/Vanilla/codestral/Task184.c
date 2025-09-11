#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define UPPERCASE_LETTERS "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define NUMBER_OF_DIGITS 3
#define NUMBER_OF_LETTERS 2
#define MAX_NAMES 676000  // 26^2 * 10^3

char existingNames[MAX_NAMES][NUMBER_OF_LETTERS + NUMBER_OF_DIGITS + 1];
int existingNamesCount = 0;

int isNameExist(char *name) {
    for (int i = 0; i < existingNamesCount; i++) {
        if (strcmp(existingNames[i], name) == 0) {
            return 1;
        }
    }
    return 0;
}

char *generateName() {
    srand(time(0));
    char *name = malloc((NUMBER_OF_LETTERS + NUMBER_OF_DIGITS + 1) * sizeof(char));
    do {
        for (int i = 0; i < NUMBER_OF_LETTERS; i++) {
            name[i] = UPPERCASE_LETTERS[rand() % 26];
        }
        for (int i = NUMBER_OF_LETTERS; i < NUMBER_OF_LETTERS + NUMBER_OF_DIGITS; i++) {
            name[i] = '0' + rand() % 10;
        }
        name[NUMBER_OF_LETTERS + NUMBER_OF_DIGITS] = '\0';
    } while (isNameExist(name));
    strcpy(existingNames[existingNamesCount], name);
    existingNamesCount++;
    return name;
}

int main() {
    printf("%s\n", generateName());
    printf("%s\n", generateName());
    printf("%s\n", generateName());
    printf("%s\n", generateName());
    printf("%s\n", generateName());
    return 0;
}