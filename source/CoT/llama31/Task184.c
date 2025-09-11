#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_NAME_LENGTH 6
#define MAX_ROBOTS 1000

char* generateRobotName(char* name, int* usedNames, int usedCount) {
    if (usedCount >= MAX_ROBOTS) {
        printf("Maximum number of unique names exceeded.\n");
        exit(1);
    }

    char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int letterLen = strlen(letters);
    int digitLen = 10;

    while (true) {
        name[0] = letters[rand() % letterLen];
        name[1] = letters[rand() % letterLen];
        name[2] = '0' + rand() % digitLen;
        name[3] = '0' + rand() % digitLen;
        name[4] = '0' + rand() % digitLen;
        name[5] = '\0';

        bool isUnique = true;
        for (int i = 0; i < usedCount; ++i) {
            if (strcmp(name, usedNames[i]) == 0) {
                isUnique = false;
                break;
            }
        }

        if (isUnique) {
            strcpy(usedNames[usedCount], name);
            return name;
        }
    }
}

int main() {
    srand(time(NULL));
    char name[MAX_NAME_LENGTH];
    char usedNames[MAX_ROBOTS][MAX_NAME_LENGTH];
    int usedCount = 0;

    for (int i = 0; i < 5; ++i) {
        printf("Robot Name: %s\n", generateRobotName(name, (int*)usedNames, usedCount++));
    }

    return 0;
}