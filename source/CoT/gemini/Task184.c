#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAMES 10000 // Adjust as needed

char usedNames[MAX_NAMES][6];
int numUsedNames = 0;

// Function to generate a random robot name
char* generateRobotName() {
    char* name = (char*)malloc(sizeof(char) * 6); 
    if (name == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE); // Handle memory allocation error
    }

    do {
        name[0] = 'A' + (rand() % 26);
        name[1] = 'A' + (rand() % 26);
        name[2] = '0' + (rand() % 10);
        name[3] = '0' + (rand() % 10);
        name[4] = '0' + (rand() % 10);
        name[5] = '\0'; // Null-terminate the string
    } while (numUsedNames > 0 && strstr((char*)usedNames, name) != NULL); // Prevent duplicates

    if (numUsedNames < MAX_NAMES) { // Check if array has space
        strcpy(usedNames[numUsedNames++], name);
    } else {
        fprintf(stderr, "Maximum number of robot names reached.\n");
    }

    return name;
}


void resetRobotName(char* name) {
    for (int i = 0; i < numUsedNames; i++) {
        if (strcmp(usedNames[i], name) == 0) {
            // Shift remaining names to fill the gap
            for (int j = i; j < numUsedNames - 1; j++) {
                strcpy(usedNames[j], usedNames[j + 1]);
            }
            numUsedNames--;
            break;
        }
    }
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    char* name1 = generateRobotName();
    printf("%s\n", name1);
    free(name1); // Free allocated memory


    char* name2 = generateRobotName();
    printf("%s\n", name2);
    free(name2);



    char* name3 = generateRobotName();
    printf("%s\n", name3);

    resetRobotName(name3);

    char* name4 = generateRobotName();
    printf("%s\n", name4);
    free(name4);

    char* name5 = generateRobotName();
    printf("%s\n", name5);
    free(name5);


    free(name3);

    return 0;
}