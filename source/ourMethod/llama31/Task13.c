#include <stdio.h>
#include <string.h>

bool isValidWalk(const char* walk[], int size) {
    if (size != 10) {
        return false;
    }
    int x = 0, y = 0;
    for (int i = 0; i < size; i++) {
        if (strcmp(walk[i], "n") == 0) {
            y++;
        } else if (strcmp(walk[i], "s") == 0) {
            y--;
        } else if (strcmp(walk[i], "e") == 0) {
            x++;
        } else if (strcmp(walk[i], "w") == 0) {
            x--;
        }
    }
    return x == 0 && y == 0;
}

int main() {
    const char* testCases[][10] = {
        {"n", "s", "n", "s", "n", "s", "n", "s", "n", "s"},
        {"w", "e", "w", "e", "w", "e", "w", "e", "w", "e"},
        {"n", "n", "n", "s", "n", "s", "n", "s", "n", "s"},
        {"e", "w", "e", "w", "e", "w", "e", "w", "e", "w"},
        {"n", "s", "e", "w", "n", "s", "e", "w", "n", "s"}
    };

    for (int i = 0; i < 5; i++) {
        printf("Walk: ");
        for (int j = 0; j < 10; j++) {
            printf("%s ", testCases[i][j]);
        }
        printf(" - Valid: %s\n", isValidWalk(testCases[i], 10) ? "true" : "false");
    }

    return 0;
}