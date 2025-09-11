#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Simple set implementation using an array for demonstration purposes
#define MAX_NAMES 1000
char names[MAX_NAMES][6];
int nameCount = 0;

void initRandom() {
    srand(time(NULL));
}

int isNameUsed(const char* name) {
    for (int i = 0; i < nameCount; i++) {
        if (strcmp(names[i], name) == 0) {
            return 1;
        }
    }
    return 0;
}

void addName(const char* name) {
    strcpy(names[nameCount], name);
    nameCount++;
}

char* generateRandomName() {
    static char name[6];
    for (int i = 0; i < 2; i++) {
        name[i] = 'A' + rand() % 26;
    }
    for (int i = 2; i < 5; i++) {
        name[i] = '0' + rand() % 10;
    }
    name[5] = '\0';
    return name;
}

char* generateRobotName() {
    while (1) {
        char* name = generateRandomName();
        if (!isNameUsed(name)) {
            addName(name);
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