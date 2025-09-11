
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_USED_NAMES 1000
#define NAME_LENGTH 6

typedef struct {
    char name[NAME_LENGTH];
} Robot;

char used_names[MAX_USED_NAMES][NAME_LENGTH];
int used_names_count = 0;

void generate_name(char* name) {
    name[0] = 'A' + (rand() % 26);
    name[1] = 'A' + (rand() % 26);
    name[2] = '0' + (rand() % 10);
    name[3] = '0' + (rand() % 10);
    name[4] = '0' + (rand() % 10);
    name[5] = '\\0';
}

int is_name_used(const char* name) {
    for (int i = 0; i < used_names_count; i++) {
        if (strcmp(used_names[i], name) == 0) {
            return 1;
        }
    }
    return 0;
}

void generate_unique_name(char* name) {
    do {
        generate_name(name);
    } while (is_name_used(name));
    
    strcpy(used_names[used_names_count], name);
    used_names_count++;
}

void robot_init(Robot* robot) {
    generate_unique_name(robot->name);
}

void robot_reset(Robot* robot) {
    generate_unique_name(robot->name);
}

const char* robot_get_name(Robot* robot) {
    return robot->name;
}

int main() {
    srand(time(NULL));
    
    // Test case 1: Create new robot
    Robot robot1;
    robot_init(&robot1);
    printf("Robot 1 name: %s\\n", robot_get_name(&robot1));
    
    // Test case 2: Name persists
    printf("Robot 1 name again: %s\\n", robot_get_name(&robot1));
    
    // Test case 3: New robot gets different name
    Robot robot2;
    robot_init(&robot2);
    printf("Robot 2 name: %s\\n", robot_get_name(&robot2));
    
    // Test case 4: Reset robot
    robot_reset(&robot1);
    printf("Robot 1 after reset: %s\\n", robot_get_name(&robot1));
    
    // Test case 5: Create multiple robots
    Robot robot3;
    robot_init(&robot3);
    printf("Robot 3 name: %s\\n", robot_get_name(&robot3));
    
    return 0;
}
