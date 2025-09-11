#include <stdio.h>
#include <string.h>

int isValidWalk(char* walk[], int length) {
    if (length != 10) return 0;
    int x = 0, y = 0;
    for (int i = 0; i < length; i++) {
        if (strcmp(walk[i], "n") == 0) y++;
        else if (strcmp(walk[i], "s") == 0) y--;
        else if (strcmp(walk[i], "e") == 0) x++;
        else if (strcmp(walk[i], "w") == 0) x--;
    }
    return x == 0 && y == 0;
}

int main() {
    char* testCases[][10] = {
        {"n", "s", "n", "s", "n", "s", "n", "s", "n", "s"},
        {"w", "e", "w", "e", "w", "e", "w", "e", "w", "e"},
        {"n", "n", "n", "s", "s", "s", "n", "s", "n", "s"},
        {"e", "w", "e", "w", "e", "w", "e", "w", "e", "w"},
        {"n", "s", "e", "w", "n", "s", "e", "w", "n", "s"}
    };
    for (int i = 0; i < 5; i++) {
        printf("%d\n", isValidWalk(testCases[i], 10));
    }
    return 0;
}