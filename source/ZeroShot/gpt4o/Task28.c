#include <stdio.h>
#include <string.h>

void formatLikes(char *buffer, size_t bufferSize, char names[][50], size_t size) {
    switch (size) {
        case 0:
            snprintf(buffer, bufferSize, "no one likes this");
            break;
        case 1:
            snprintf(buffer, bufferSize, "%s likes this", names[0]);
            break;
        case 2:
            snprintf(buffer, bufferSize, "%s and %s like this", names[0], names[1]);
            break;
        case 3:
            snprintf(buffer, bufferSize, "%s, %s and %s like this", names[0], names[1], names[2]);
            break;
        default:
            snprintf(buffer, bufferSize, "%s, %s and %zu others like this", names[0], names[1], size - 2);
            break;
    }
}

int main() {
    char buffer[100];

    char names1[][50] = {};
    formatLikes(buffer, sizeof(buffer), names1, 0);
    printf("%s\n", buffer); // "no one likes this"

    char names2[][50] = {"Peter"};
    formatLikes(buffer, sizeof(buffer), names2, 1);
    printf("%s\n", buffer); // "Peter likes this"

    char names3[][50] = {"Jacob", "Alex"};
    formatLikes(buffer, sizeof(buffer), names3, 2);
    printf("%s\n", buffer); // "Jacob and Alex like this"

    char names4[][50] = {"Max", "John", "Mark"};
    formatLikes(buffer, sizeof(buffer), names4, 3);
    printf("%s\n", buffer); // "Max, John and Mark like this"

    char names5[][50] = {"Alex", "Jacob", "Mark", "Max"};
    formatLikes(buffer, sizeof(buffer), names5, 4);
    printf("%s\n", buffer); // "Alex, Jacob and 2 others like this"

    return 0;
}