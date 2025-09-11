
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ROBOTS 1000
#define NAME_LENGTH 6

char used_names[MAX_ROBOTS][NAME_LENGTH];
int used_names_count = 0;

int name_exists(const char* name) {
    for (int i = 0; i < used_names_count; i++) {
        if (strcmp(used_names[i], name) == 0) {
            return 1;
        }
    }
    return 0;
}

void generate_name(char* name) {
    // Generate 2 uppercase letters
    name[0] = 'A' + (rand() % 26);
    name[1] = 'A' + (rand() % 26);
    // Generate 3 digits
    for (int i = 0; i < 3; i++) {
        name[i + 2] = '0' + (rand() % 10);
    }
    name[5] = '\\0';
}

void generate_unique_name(char* name) {
    do {
        generate_name(name);
    } while (name_exists(name));
    
    strcpy(used_names[used_names_count], name);
    used_names_count++;
}

typedef struct {
    char name[NAME_LENGTH];
} Robot;

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
    
    // Test cases
    Robot robots[5];
    for (int i = 0; i < 5; i++) {
        robot_init(&robots[i]);
        printf("Robot %d name: %s\\n", i+1, robot_get_name(&robots[i]));
        if (i % 2 == 0) {
            printf("Resetting Robot %d\\n", i+1);
            robot_reset(&robots[i]);
            printf("Robot %d new name: %s\\n", i+1, robot_get_name(&robots[i]));
        }
    }
    
    return 0;
}
