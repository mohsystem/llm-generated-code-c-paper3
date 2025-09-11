#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NAME_LENGTH 6

typedef struct {
    char name[NAME_LENGTH];
} Robot;

static char usedNames[10000][NAME_LENGTH];
static int usedNamesCount = 0;

void generateName(char* name) {
    int isUnique;
    do {
        isUnique = 1;
        name[0] = 'A' + rand() % 26;
        name[1] = 'A' + rand() % 26;
        name[2] = '0' + rand() % 10;
        name[3] = '0' + rand() % 10;
        name[4] = '0' + rand() % 10;
        name[5] = '\0';

        for (int i = 0; i < usedNamesCount; ++i) {
            if (strcmp(usedNames[i], name) == 0) {
                isUnique = 0;
                break;
            }
        }
    } while (!isUnique);

    strcpy(usedNames[usedNamesCount++], name);
}

void resetRobot(Robot* robot) {
    generateName(robot->name);
}

int main() {
    srand(time(NULL));

    Robot robot1, robot2, robot3, robot4, robot5;

    resetRobot(&robot1);
    resetRobot(&robot2);
    resetRobot(&robot3);
    resetRobot(&robot4);
    resetRobot(&robot5);

    printf("%s\n", robot1.name);
    printf("%s\n", robot2.name);
    printf("%s\n", robot3.name);
    printf("%s\n", robot4.name);
    printf("%s\n", robot5.name);

    resetRobot(&robot1);
    printf("%s\n", robot1.name);

    return 0;
}