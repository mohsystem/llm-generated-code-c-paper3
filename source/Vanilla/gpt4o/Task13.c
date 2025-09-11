#include <stdio.h>
#include <stdbool.h>

bool isValidWalk(char walk[], int size) {
    if (size != 10) return false;
    int ns = 0, ew = 0;
    for (int i = 0; i < size; i++) {
        switch (walk[i]) {
            case 'n': ns++; break;
            case 's': ns--; break;
            case 'e': ew++; break;
            case 'w': ew--; break;
        }
    }
    return ns == 0 && ew == 0;
}

int main() {
    printf("%d\n", isValidWalk((char[]){'n','s','n','s','n','s','n','s','n','s'}, 10)); // true
    printf("%d\n", isValidWalk((char[]){'w','e','w','e','w','e','w','e','w','e'}, 10)); // true
    printf("%d\n", isValidWalk((char[]){'n','n','n','n','n','n','n','n','n','n'}, 10)); // false
    printf("%d\n", isValidWalk((char[]){'n','s','e','w','n','s','e','w','n','s'}, 10)); // true
    printf("%d\n", isValidWalk((char[]){'n','s','e','w','n','s','e','w','n'}, 9));      // false
    return 0;
}