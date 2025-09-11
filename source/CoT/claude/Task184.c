
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

char used_names[MAX_ROBOTS][NAME_LENGTH];
int used_names_count = 0;

bool is_name_used(const char* name) {
    for (int i = 0; i < used_names_count; i++) {
        if (strcmp(used_names[i], name) == 0) {
            return true;
        }
    }
    return false;
}

void generate_unique_name(char* name) {
    do {
        // Generate two random uppercase letters
        name[0] = 'A' + (rand() % 26);
        name[1] = 'A' + (rand() % 26);
        
        // Generate three random digits
        for (int i = 0; i < 3; i++) {
            name[i + 2] = '0' + (rand() % 10);
        }
        name[5] = '\\0';
    } while (is_name_used(name) && used_names_count < MAX_ROBOTS);

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

    // Test cases
    for (int i = 0; i < 5; i++) {
        Robot robot;
        robot_init(&robot);
        printf("Robot %d initial name: %s\\n", i+1, robot_get_name(&robot));
        robot_reset(&robot);
        printf("Robot %d after reset: %s\\n", i+1, robot_get_name(&robot));
    }

    return 0;
}
