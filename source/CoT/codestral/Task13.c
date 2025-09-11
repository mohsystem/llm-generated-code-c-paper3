#include <stdio.h>
#include <stdbool.h>

bool isValidWalk(const char *walk, int size) {
    if (size != 10) return false;
    int x = 0;
    int y = 0;
    for (int i = 0; i < size; i++) {
        char c = walk[i];
        if (c == 'n') y++;
        else if (c == 's') y--;
        else if (c == 'e') x++;
        else if (c == 'w') x--;
    }
    return x == 0 && y == 0;
}

int main() {
    printf("%s\n", isValidWalk((const char[]){'n','s','n','s','n','s','n','s','n','s'}, 10) ? "true" : "false");
    printf("%s\n", isValidWalk((const char[]){'w','e','w','e','w','e','w','e','w','e','w','e'}, 12) ? "true" : "false");
    printf("%s\n", isValidWalk((const char[]){'w'}, 1) ? "true" : "false");
    printf("%s\n", isValidWalk((const char[]){'n','n','n','s','n','s','n','s','n','s'}, 10) ? "true" : "false");
    return 0;
}