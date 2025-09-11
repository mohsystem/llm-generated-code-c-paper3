#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* likes(const char* names[], int len) {
    char* result = malloc(256 * sizeof(char));
    if (len == 0) {
        strcpy(result, "no one likes this");
    } else if (len == 1) {
        sprintf(result, "%s likes this", names[0]);
    } else if (len == 2) {
        sprintf(result, "%s and %s like this", names[0], names[1]);
    } else if (len == 3) {
        sprintf(result, "%s, %s and %s like this", names[0], names[1], names[2]);
    } else {
        sprintf(result, "%s, %s and %d others like this", names[0], names[1], len - 2);
    }
    return result;
}

int main() {
    const char* names1[] = {};
    printf("%s\n", likes(names1, 0));

    const char* names2[] = {"Peter"};
    printf("%s\n", likes(names2, 1));

    const char* names3[] = {"Jacob", "Alex"};
    printf("%s\n", likes(names3, 2));

    const char* names4[] = {"Max", "John", "Mark"};
    printf("%s\n", likes(names4, 3));

    const char* names5[] = {"Alex", "Jacob", "Mark", "Max"};
    printf("%s\n", likes(names5, 4));

    return 0;
}