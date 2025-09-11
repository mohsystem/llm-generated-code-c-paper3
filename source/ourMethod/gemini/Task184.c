#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAMES 10000 // Adjust as needed

char usedNames[MAX_NAMES][6];
int numNames = 0;

// Function to generate a random robot name
char* generateRobotName() {
    char* name = (char*)malloc(sizeof(char) * 6);
    if (name == NULL) {
        return NULL; // Handle memory allocation error
    }

    do {
        // Generate random uppercase letters
        for (int i = 0; i < 2; i++) {
            name[i] = 'A' + (rand() % 26);
        }

        // Generate random digits
        for (int i = 2; i < 5; i++) {
            name[i] = '0' + (rand() % 10);
        }
        name[5] = '\0';

        // Check for collisions (ensure uniqueness)
        int collision = 0;
        for (int i = 0; i < numNames; i++) {
            if (strcmp(name, usedNames[i]) == 0) {
                collision = 1;
                break;
            }
        }
        if (!collision) {
            if (numNames < MAX_NAMES) {
              strcpy(usedNames[numNames++], name);
            }
            
            return name;
        }
       

    } while (1);
}

// Function to reset a robot name
void resetRobotName(char* name) {
    for (int i = 0; i < numNames; i++) {
        if (strcmp(name, usedNames[i]) == 0) {
          // Shift elements to remove the name
          for (int j = i; j < numNames - 1; j++) {
              strcpy(usedNames[j], usedNames[j + 1]);
          }
          numNames--;
          break; 
        }
    }
    free(name);
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    char *n1 = generateRobotName();
    printf("%s\n", n1);

    char *n2 = generateRobotName();
    printf("%s\n", n2);

    char *n3 = generateRobotName();
    printf("%s\n", n3);

    resetRobotName(n2); // Reset one of the names


    char *n4 = generateRobotName();
    printf("%s\n", n4);

    char *n5 = generateRobotName();
    printf("%s\n", n5);

    resetRobotName(n1);
    resetRobotName(n3);
    resetRobotName(n4);
    resetRobotName(n5);

    return 0;
}