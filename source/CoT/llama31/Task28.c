#include <stdio.h>
#include <string.h>

void likes(char** names, int len, char* buffer) {
    if (len == 0) {
        strcpy(buffer, "no one likes this");
    } else if (len == 1) {
        sprintf(buffer, "%s likes this", names[0]);
    } else if (len == 2) {
        sprintf(buffer, "%s and %s like this", names[0], names[1]);
    } else if (len == 3) {
        sprintf(buffer, "%s, %s and %s like this", names[0], names[1], names[2]);
    } else {
        sprintf(buffer, "%s, %s and %d others like this", names[0], names[1], len - 2);
    }
}

int main() {
    char* testCases[][4] = {
        {},
        {"Peter"},
        {"Jacob", "Alex"},
        {"Max", "John", "Mark"},
        {"Alex", "Jacob", "Mark", "Max"}
    };
    int testCaseLens[] = {0, 1, 2, 3, 4};
    char buffer[100];

    for (int i = 0; i < 5; i++) {
        likes(testCases[i], testCaseLens[i], buffer);
        printf("%s\n", buffer);
    }

    return 0;
}