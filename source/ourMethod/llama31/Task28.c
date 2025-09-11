#include <stdio.h>
#include <string.h>

void getLikesText(char** names, int length) {
    if (length == 0) {
        printf("no one likes this\n");
    } else if (length == 1) {
        printf("%s likes this\n", names[0]);
    } else if (length == 2) {
        printf("%s and %s like this\n", names[0], names[1]);
    } else {
        printf("%s, %s and %d others like this\n", names[0], names[1], length - 2);
    }
}

int main() {
    char* testCases[][4] = {
        {NULL},
        {"Peter", NULL},
        {"Jacob", "Alex", NULL},
        {"Max", "John", "Mark", NULL},
        {"Alex", "Jacob", "Mark", "Max", NULL}
    };

    int lengths[] = {0, 1, 2, 3, 4};

    for (int i = 0; i < 5; i++) {
        getLikesText(testCases[i], lengths[i]);
    }

    return 0;
}