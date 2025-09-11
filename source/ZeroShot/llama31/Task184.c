#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_ROBOTS 1000
#define NAME_LENGTH 5

static char usedNames[MAX_ROBOTS][NAME_LENGTH + 1];
static int usedCount = 0;

void initRandom() {
    srand(time(NULL));
}

int isNameUsed(const char *name) {
    for (int i = 0; i < usedCount; i++) {
        if (strcmp(usedNames[i], name) == 0) {
            return 1;
        }
    }
    return 0;
}

void addUsedName(const char *name) {
    strcpy(usedNames[usedCount], name);
    usedCount++;
}

char *generateRobotName() {
    static char name[NAME_LENGTH + 1];
    while (true) {
        name[0] = 'A' + (rand() % 26);
        name[1] = 'A' + (rand() % 26);
        sprintf(name + 2, "%03d", rand() % 1000);
        if (!isNameUsed(name)) {
            addUsedName(name);
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