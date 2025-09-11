#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAMES 10000 // Adjust as needed

char robotNames[MAX_NAMES][6];
int numRobots = 0;

char* generateRobotName() {
    char name[6];
    do {
        for (int i = 0; i < 2; i++) {
            name[i] = 'A' + (rand() % 26);
        }
        for (int i = 2; i < 5; i++) {
            name[i] = '0' + (rand() % 10);
        }
        name[5] = '\0';
    } while (numRobots > 0 && (bsearch(name, robotNames, numRobots, 6, (int (*)(const void *, const void *))strcmp) != NULL));

    if (numRobots < MAX_NAMES) {
        strcpy(robotNames[numRobots], name);
        qsort(robotNames, numRobots + 1, 6, (int (*)(const void *, const void *))strcmp); // Keep sorted for bsearch
        numRobots++;
        return robotNames[numRobots -1]; // Return the newly added name

    } else {
       return NULL; // Handle the case where the maximum number of robots is reached
    }
}


void resetRobotName(const char* name) {
    char** found = (char**)bsearch(name, robotNames, numRobots, 6, (int (*)(const void *, const void *))strcmp);
    if (found) {
        //shift elements after found one position to left to overwrite found
        for(int i=found-robotNames; i<numRobots-1; ++i){
           strcpy(robotNames[i], robotNames[i+1]);
        }

        numRobots--;

    }
}


int main() {
    srand(time(NULL));

    char *name1 = generateRobotName();
    printf("%s\n", name1);
    char *name2 = generateRobotName();
    printf("%s\n", name2);
    char *name3 = generateRobotName();
    printf("%s\n", name3);


    resetRobotName(name2);

    char *name4 = generateRobotName();
    printf("%s\n", name4);
    char *name5 = generateRobotName();
    printf("%s\n", name5);

    return 0;
}