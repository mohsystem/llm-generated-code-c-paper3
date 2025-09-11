
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_ROBOTS 1000
#define NAME_LENGTH 6

typedef struct {
    char name[NAME_LENGTH];
} Robot;

typedef struct {
    char names[MAX_ROBOTS][NAME_LENGTH];
    int count;
} UsedNames;

UsedNames usedNames = {{0}, 0};

bool isNameUsed(const char* name) {
    for(int i = 0; i < usedNames.count; i++) {
        if(strcmp(usedNames.names[i], name) == 0) {
            return true;
        }
    }
    return false;
}

void generateUniqueName(char* name) {
    static const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    do {
        // Generate 2 random uppercase letters
        name[0] = letters[rand() % 26];
        name[1] = letters[rand() % 26];
        
        // Generate 3 random digits
        for(int i = 0; i < 3; i++) {
            name[2 + i] = '0' + (rand() % 10);
        }
        name[5] = '\\0';
    } while(isNameUsed(name) && usedNames.count < MAX_ROBOTS);
    
    strcpy(usedNames.names[usedNames.count], name);
    usedNames.count++;
}

void resetRobot(Robot* robot) {
    generateUniqueName(robot->name);
}

Robot* createRobot() {
    Robot* robot = (Robot*)malloc(sizeof(Robot));
    if(robot != NULL) {
        resetRobot(robot);
    }
    return robot;
}

void destroyRobot(Robot* robot) {
    free(robot);
}

int main() {
    srand(time(NULL));
    
    // Test cases
    Robot* robot1 = createRobot();
    printf("Robot 1: %s\\n", robot1->name);
    printf("Same name: %s\\n", robot1->name);
    
    Robot* robot2 = createRobot();
    printf("Robot 2: %s\\n", robot2->name);
    
    resetRobot(robot1);
    printf("Robot 1 after reset: %s\\n", robot1->name);
    
    Robot* robot3 = createRobot();
    printf("Robot 3: %s\\n", robot3->name);
    
    Robot* robot4 = createRobot();
    printf("Robot 4: %s\\n", robot4->name);
    
    // Clean up
    destroyRobot(robot1);
    destroyRobot(robot2);
    destroyRobot(robot3);
    destroyRobot(robot4);
    
    return 0;
}
