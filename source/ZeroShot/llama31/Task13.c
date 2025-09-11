#include <stdio.h>
#include <stdbool.h>

bool isValidWalk(const char* walk[], int size) {
    if (size != 10) {
        return false;
    }
    int x = 0, y = 0;
    for (int i = 0; i < size; i++) {
        if (walk[i][0] == 'n') {
            y++;
        } else if (walk[i][0] == 's') {
            y--;
        } else if (walk[i][0] == 'e') {
            x++;
        } else if (walk[i][0] == 'w') {
            x--;
        }
    }
    return x == 0 && y == 0;
}

int main() {
    const char* testCases[][10] = {
        {"n", "s", "n", "s", "n", "s", "n", "s", "n", "s"},
        {"w", "e", "w", "e", "w", "e", "w", "e", "w", "e"},
        {"n", "n", "n", "s", "s", "s", "e", "e", "w", "w"},
        {"n", "s", "n", "s", "n", "s", "n", "s", "n", "s", "n"}, // This case will be ignored due to size mismatch
        {"w", "e", "w", "e", "w", "e", "w"}
    };

    const int sizes[] = {10, 10, 10, 11, 6}; // Sizes of each test case

    for (int i = 0; i < 5; i++) {
        if (sizes[i] == 10) {
            printf("%d\n", isValidWalk(testCases[i], sizes[i]));
        }
    }

    return 0;
}