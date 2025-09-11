#include <stdio.h>
#include <stdbool.h>

bool isValidWalk(const char *walk, int length) {
    if (length != 10) return false;
    int ns = 0, ew = 0;
    for (int i = 0; i < length; i++) {
        switch (walk[i]) {
            case 'n': ns++; break;
            case 's': ns--; break;
            case 'e': ew++; break;
            case 'w': ew--; break;
            default: return false; // Invalid direction
        }
    }
    return ns == 0 && ew == 0;
}

int main() {
    printf("%s\n", isValidWalk("nsnsnsnsns", 10) ? "true" : "false");
    printf("%s\n", isValidWalk("wewewewewewe", 12) ? "true" : "false");
    printf("%s\n", isValidWalk("nnnsssnsns", 10) ? "true" : "false");
    printf("%s\n", isValidWalk("nsewnsewns", 10) ? "true" : "false");
    printf("%s\n", isValidWalk("nnnnnsssss", 10) ? "true" : "false");
    return 0;
}