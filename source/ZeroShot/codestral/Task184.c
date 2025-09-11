// Due to the limitations of C, it's not possible to use dynamic data structures like a HashSet to store existing names.
// Instead, a simple array with a fixed size is used. If the generated name already exists, a new name is generated.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAMES 676000
#define NAME_LEN 5

char existingNames[MAX_NAMES][NAME_LEN + 1];
int nameCount = 0;

char generateName() {
    const char UPPER[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char DIGITS[] = "0123456789";

    char name[NAME_LEN + 1];
    int i, exists;

    srand(time(0));

    do {
        exists = 0;

        name[0] = UPPER[rand() % 26];
        name[1] = UPPER[rand() % 26];
        name[2] = DIGITS[rand() % 10];
        name[3] = DIGITS[rand() % 10];
        name[4] = DIGITS[rand() % 10];
        name[5] = '\0';

        for (i = 0; i < nameCount; i++) {
            if (strcmp(existingNames[i], name) == 0) {
                exists = 1;
                break;
            }
        }
    } while (exists);

    strcpy(existingNames[nameCount++], name);

    return name;
}

int main() {
    int i;
    for (i = 0; i < 5; i++) {
        printf("%s\n", generateName());
    }
    return 0;
}