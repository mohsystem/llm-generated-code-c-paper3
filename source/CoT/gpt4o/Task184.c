#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char name[6];
} Task184;

static char existingNames[100][6];
static int nameCount = 0;

void generateRandomName(char* buffer) {
    for (int i = 0; i < 2; ++i) {
        buffer[i] = 'A' + rand() % 26;
    }
    int number = rand() % 1000;
    snprintf(buffer + 2, 4, "%03d", number);
}

int isNameUnique(const char* name) {
    for (int i = 0; i < nameCount; ++i) {
        if (strcmp(existingNames[i], name) == 0) {
            return 0;
        }
    }
    return 1;
}

void reset(Task184* robot) {
    char newName[6];
    do {
        generateRandomName(newName);
    } while (!isNameUnique(newName));
    
    if (robot->name[0] != '\0') {
        for (int i = 0; i < nameCount; ++i) {
            if (strcmp(existingNames[i], robot->name) == 0) {
                for (int j = i; j < nameCount - 1; ++j) {
                    strcpy(existingNames[j], existingNames[j + 1]);
                }
                --nameCount;
                break;
            }
        }
    }
    
    strcpy(robot->name, newName);
    strcpy(existingNames[nameCount++], newName);
}

const char* getName(Task184* robot) {
    return robot->name;
}

int main() {
    srand((unsigned) time(NULL));

    Task184 robot1 = {{0}};
    Task184 robot2 = {{0}};
    Task184 robot3 = {{0}};
    Task184 robot4 = {{0}};
    Task184 robot5 = {{0}};

    reset(&robot1);
    reset(&robot2);
    reset(&robot3);
    reset(&robot4);
    reset(&robot5);

    printf("%s\n", getName(&robot1));
    printf("%s\n", getName(&robot2));
    printf("%s\n", getName(&robot3));
    printf("%s\n", getName(&robot4));
    printf("%s\n", getName(&robot5));

    reset(&robot1);
    printf("%s\n", getName(&robot1));

    return 0;
}