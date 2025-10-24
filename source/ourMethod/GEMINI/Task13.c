#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Determines if a given walk is valid.
 * A valid walk takes exactly 10 minutes and returns to the starting point.
 * 
 * @param walk An array of characters representing directions ('n', 's', 'e', 'w').
 * @param len The length of the walk array.
 * @return true if the walk is valid, false otherwise.
 */
bool isValidWalk(const char walk[], size_t len) {
    if (len != 10) {
        return false;
    }

    int x = 0; // East-West displacement
    int y = 0; // North-South displacement

    for (size_t i = 0; i < len; ++i) {
        switch (walk[i]) {
            case 'n': y++; break;
            case 's': y--; break;
            case 'e': x++; break;
            case 'w': x--; break;
            default:
                // Per the prompt, input is always valid, so no action needed.
                break;
        }
    }

    return x == 0 && y == 0;
}

int main() {
    // Test Case 1: Valid walk
    char walk1[] = {'n','s','n','s','n','s','n','s','n','s'};
    printf("Test 1: %s\n", isValidWalk(walk1, sizeof(walk1)/sizeof(walk1[0])) ? "true" : "false");

    // Test Case 2: Too long
    char walk2[] = {'w','e','w','e','w','e','w','e','w','e','w','e'};
    printf("Test 2: %s\n", isValidWalk(walk2, sizeof(walk2)/sizeof(walk2[0])) ? "true" : "false");

    // Test Case 3: Too short
    char walk3[] = {'w'};
    printf("Test 3: %s\n", isValidWalk(walk3, sizeof(walk3)/sizeof(walk3[0])) ? "true" : "false");

    // Test Case 4: Correct length, but does not return to start
    char walk4[] = {'n','n','n','s','n','s','n','s','n','s'};
    printf("Test 4: %s\n", isValidWalk(walk4, sizeof(walk4)/sizeof(walk4[0])) ? "true" : "false");
    
    // Test Case 5: Valid walk, different order
    char walk5[] = {'e', 'w', 'e', 'w', 'n', 's', 'n', 's', 'e', 'w'};
    printf("Test 5: %s\n", isValidWalk(walk5, sizeof(walk5)/sizeof(walk5[0])) ? "true" : "false");
    
    return 0;
}