#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isValidWalk(const char* walk[], int length) {
    if (length != 10) return false;

    int x = 0, y = 0;
    for (int i = 0; i < length; i++) {
        if (strcmp(walk[i], "n") == 0) y++;
        else if (strcmp(walk[i], "s") == 0) y--;
        else if (strcmp(walk[i], "e") == 0) x++;
        else if (strcmp(walk[i], "w") == 0) x--;
        else return false; // Invalid direction
    }
    return x == 0 && y == 0;
}

int main() {
    const char* walk1[] = {"n", "s", "n", "s", "n", "s", "n", "s", "n", "s"};
    const char* walk2[] = {"n", "n", "n", "s", "s", "s", "e", "w", "e", "w"};
    const char* walk3[] = {"n", "s", "n", "s", "n", "s", "n", "s", "e", "w"};
    const char* walk4[] = {"e", "w", "e", "w", "e", "w", "e", "w", "e", "w"};
    const char* walk5[] = {"n", "e", "n", "e", "n", "e", "n", "e", "n", "e"};

    printf("%d\n", isValidWalk(walk1, 10)); // true
    printf("%d\n", isValidWalk(walk2, 10)); // false
    printf("%d\n", isValidWalk(walk3, 10)); // true
    printf("%d\n", isValidWalk(walk4, 10)); // true
    printf("%d\n", isValidWalk(walk5, 10)); // false

    return 0;
}