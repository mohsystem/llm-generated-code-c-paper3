#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NAME_LENGTH 6
#define MAX_ROBOTS 10000

typedef struct {
    char name[NAME_LENGTH];
} Task184;

static char usedNames[MAX_ROBOTS][NAME_LENGTH];
static int usedCount = 0;

char *generateRandomName() {
    static char name[NAME_LENGTH];
    name[0] = 'A' + rand() % 26;
    name[1] = 'A' + rand() % 26;
    name[2] = '0' + rand() % 10;
    name[3] = '0' + rand() % 10;
    name[4] = '0' + rand() % 10;
    name[5] = '\0';
    return name;
}

int isNameUsed(char *name) {
    for (int i = 0; i < usedCount; i++) {
        if (strcmp(usedNames[i], name) == 0) {
            return 1;
        }
    }
    return 0;
}

void addNameToUsed(char *name) {
    strcpy(usedNames[usedCount++], name);
}

void removeNameFromUsed(char *name) {
    for (int i = 0; i < usedCount; i++) {
        if (strcmp(usedNames[i], name) == 0) {
            strcpy(usedNames[i], usedNames[--usedCount]);
            break;
        }
    }
}

void initTask184(Task184 *robot) {
    strcpy(robot->name, "");
    reset(robot);
}

char *getName(Task184 *robot) {
    if (strlen(robot->name) == 0) {
        reset(robot);
    }
    return robot->name;
}

void reset(Task184 *robot) {
    char *newName;
    do {
        newName = generateRandomName();
    } while (isNameUsed(newName));
    if (strlen(robot->name) > 0) {
        removeNameFromUsed(robot->name);
    }
    strcpy(robot->name, newName);
    addNameToUsed(robot->name);
}

int main() {
    srand(time(0));

    Task184 robot1;
    initTask184(&robot1);
    printf("%s\n", getName(&robot1));
    reset(&robot1);
    printf("%s\n", getName(&robot1));

    Task184 robot2;
    initTask184(&robot2);
    printf("%s\n", getName(&robot2));

    Task184 robot3;
    initTask184(&robot3);
    printf("%s\n", getName(&robot3));

    Task184 robot4;
    initTask184(&robot4);
    printf("%s\n", getName(&robot4));

    Task184 robot5;
    initTask184(&robot5);
    printf("%s\n", getName(&robot5));

    return 0;
}