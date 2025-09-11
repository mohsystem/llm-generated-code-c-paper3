#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NAME_LENGTH 6

typedef struct {
    char name[NAME_LENGTH];
} Task184;

static char usedNames[1000][NAME_LENGTH]; // crude method for demonstration purposes
static int usedNamesCount = 0;

void generateRandomName(char *name) {
    name[0] = 'A' + rand() % 26;
    name[1] = 'A' + rand() % 26;
    sprintf(name + 2, "%03d", rand() % 1000);
}

int isNameUsed(const char *name) {
    for (int i = 0; i < usedNamesCount; i++) {
        if (strcmp(usedNames[i], name) == 0) {
            return 1;
        }
    }
    return 0;
}

void Task184_init(Task184 *robot) {
    Task184_reset(robot);
}

const char* Task184_getName(Task184 *robot) {
    return robot->name;
}

void Task184_reset(Task184 *robot) {
    do {
        generateRandomName(robot->name);
    } while (isNameUsed(robot->name));
    strcpy(usedNames[usedNamesCount++], robot->name);
}

int main() {
    srand(time(0));

    Task184 robot1;
    Task184_init(&robot1);
    printf("Robot1: %s\n", Task184_getName(&robot1));
    Task184_reset(&robot1);
    printf("Robot1 after reset: %s\n", Task184_getName(&robot1));

    Task184 robot2;
    Task184_init(&robot2);
    printf("Robot2: %s\n", Task184_getName(&robot2));

    Task184 robot3;
    Task184_init(&robot3);
    printf("Robot3: %s\n", Task184_getName(&robot3));

    Task184 robot4;
    Task184_init(&robot4);
    printf("Robot4: %s\n", Task184_getName(&robot4));

    Task184 robot5;
    Task184_init(&robot5);
    printf("Robot5: %s\n", Task184_getName(&robot5));

    return 0;
}