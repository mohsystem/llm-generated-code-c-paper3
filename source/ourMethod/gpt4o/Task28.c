#include <stdio.h>

const char* whoLikesIt(const char** names, int length) {
    static char buffer[256];
    switch (length) {
        case 0:
            return "no one likes this";
        case 1:
            snprintf(buffer, sizeof(buffer), "%s likes this", names[0]);
            break;
        case 2:
            snprintf(buffer, sizeof(buffer), "%s and %s like this", names[0], names[1]);
            break;
        case 3:
            snprintf(buffer, sizeof(buffer), "%s, %s and %s like this", names[0], names[1], names[2]);
            break;
        default:
            snprintf(buffer, sizeof(buffer), "%s, %s and %d others like this", names[0], names[1], length - 2);
            break;
    }
    return buffer;
}

int main() {
    const char* empty[] = {};
    const char* one[] = {"Peter"};
    const char* two[] = {"Jacob", "Alex"};
    const char* three[] = {"Max", "John", "Mark"};
    const char* four[] = {"Alex", "Jacob", "Mark", "Max"};
    
    printf("%s\n", whoLikesIt(empty, 0)); // "no one likes this"
    printf("%s\n", whoLikesIt(one, 1)); // "Peter likes this"
    printf("%s\n", whoLikesIt(two, 2)); // "Jacob and Alex like this"
    printf("%s\n", whoLikesIt(three, 3)); // "Max, John and Mark like this"
    printf("%s\n", whoLikesIt(four, 4)); // "Alex, Jacob and 2 others like this"
    
    return 0;
}