#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_NAME_LENGTH 6
#define MAX_ROBOTS 1000

char existingNames[MAX_ROBOTS][MAX_NAME_LENGTH];
int existingNamesCount = 0;

void initRandom() {
    srand(time(NULL));
}

char getRandomLetter() {
    return 'A' + (rand() % 26);
}

char getRandomDigit() {
    return '0' + (rand() % 10);
}

char* generateRandomName() {
    static char name[MAX_NAME_LENGTH];
    for (int i = 0; i < 2; i++) {
        name[i] = getRandomLetter();
    }
    for (int i = 2; i < 5; i++) {
        name[i] = getRandomDigit();
    }
    name[5] = '\0';
    return name;
}

int isNameExisting(const char* name) {
    for (int i = 0; i < existingNamesCount; i++) {
        if (strcmp(existingNames[i], name) == 0) {
            return 1;
        }
    }
    return 0;
}

void addExistingName(const char* name) {
    strcpy(existingNames[existingNamesCount], name);
    existingNamesCount++;
}

char* generateRobotName() {
    while (1) {
        char* name = generateRandomName();
        if (!isNameExisting(name)) {
            addExistingName(name);
            return name;
        }
    }
}

int main() {
    initRandom();
    for (int i = 0; i < 5; i++) {
        printf("Robot Name: %s\n", generateRobotName());
    }
    return 0;
}