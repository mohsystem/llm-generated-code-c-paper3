#include <stdio.h>
#include <stdbool.h>

bool isValidWalk(char* walk[], int length) {
    if (length != 10) return false;
    int ns = 0, ew = 0;
    for (int i = 0; i < length; i++) {
        if (strcmp(walk[i], "n") == 0) ns++;
        else if (strcmp(walk[i], "s") == 0) ns--;
        else if (strcmp(walk[i], "e") == 0) ew++;
        else if (strcmp(walk[i], "w") == 0) ew--;
    }
    return ns == 0 && ew == 0;
}

int main() {
    char* testCases[][10] = {
        {"n", "s", "n", "s", "n", "s", "n", "s", "n", "s"},
        {"w", "e", "w", "e", "w", "e", "w", "e", "w", "e"},
        {"n", "n", "n", "s", "n", "s", "n", "s", "n", "s"},
        {"n", "s", "n", "s", "n", "s", "n", "n", "n", "s"},
        {"e", "w", "e", "w", "e", "w", "e", "w", "e", "w"}
    };

    for (int i = 0; i < 5; i++) {
        printf("%d\n", isValidWalk(testCases[i], 10));
    }

    return 0;
}