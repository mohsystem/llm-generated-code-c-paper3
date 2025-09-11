#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_NAMES 10000
#define NAME_LENGTH 6

char existingNames[MAX_NAMES][NAME_LENGTH];
int nameCount = 0;

char* generateName() {
    char* newName = (char*)malloc(NAME_LENGTH * sizeof(char));
    bool isUnique;
    do {
        isUnique = true;
        for (int i = 0; i < 2; i++) {
            newName[i] = 'A' + rand() % 26;
        }
        for (int i = 2; i < NAME_LENGTH - 1; i++) {
            newName[i] = '0' + rand() % 10;
        }
        newName[NAME_LENGTH - 1] = '\0';
        for (int i = 0; i < nameCount; i++) {
            if (strcmp(newName, existingNames[i]) == 0) {
                isUnique = false;
                break;
            }
        }
    } while (!isUnique);
    strcpy(existingNames[nameCount], newName);
    nameCount++;
    return newName;
}

void resetName(char** name) {
    free(*name);
    *name = NULL;
}

char* getName(char** name) {
    if (*name == NULL) {
        *name = generateName();
    }
    return *name;
}

int main() {
    srand(time(NULL));
    char* robot1Name = NULL;
    char* robot2Name = NULL;
    printf("%s\n", getName(&robot1Name));
    printf("%s\n", getName(&robot2Name));
    resetName(&robot1Name);
    printf("%s\n", getName(&robot1Name));
    printf("%s\n", getName(&robot2Name));
    return 0;
}