#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAMES 1000 // Adjust as needed

char used_names[MAX_NAMES][6];
int num_names = 0;

// Function to generate a random robot name
char* generate_robot_name() {
    char name[6];
    do {
        for (int i = 0; i < 2; i++) {
            name[i] = 'A' + (rand() % 26);
        }
        sprintf(name + 2, "%03d", rand() % 1000);
        name[5] = '\0';

        // Check for collisions
        int collision = 0;
        for (int i = 0; i < num_names; i++) {
            if (strcmp(name, used_names[i]) == 0) {
                collision = 1;
                break;
            }
        }
        if (!collision) {
            strcpy(used_names[num_names++], name);
            return strdup(name); // Allocate memory and return a copy
        }
    } while (1);
}


void reset_robot_name(const char* name) {
    for (int i = 0; i < num_names; i++) {
        if (strcmp(name, used_names[i]) == 0) {
            // Remove the name by shifting subsequent names
            for (int j = i; j < num_names - 1; j++) {
                strcpy(used_names[j], used_names[j + 1]);
            }
            num_names--;
            break;
        }
    }
}

int main() {
    srand(time(NULL)); // Seed the random number generator


    char* robot1 = generate_robot_name();
    char* robot2 = generate_robot_name();
    char* robot3 = generate_robot_name();
    char* robot4 = generate_robot_name();
    char* robot5 = generate_robot_name();


    printf("Robot 1: %s\n", robot1);
    printf("Robot 2: %s\n", robot2);
    printf("Robot 3: %s\n", robot3);
    printf("Robot 4: %s\n", robot4);
    printf("Robot 5: %s\n", robot5);

    reset_robot_name(robot3);
    char *newRobot3 = generate_robot_name();
    printf("New Robot 3: %s\n", newRobot3);

     free(robot1);
    free(robot2);
    free(robot3);
    free(robot4);
    free(robot5);
    free(newRobot3);

    return 0;
}