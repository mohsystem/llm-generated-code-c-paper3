#include <stdio.h>
#include <string.h>

void likes(char *names[], int n, char *result) {
    switch (n) {
        case 0: strcpy(result, "no one likes this"); break;
        case 1: sprintf(result, "%s likes this", names[0]); break;
        case 2: sprintf(result, "%s and %s like this", names[0], names[1]); break;
        case 3: sprintf(result, "%s, %s and %s like this", names[0], names[1], names[2]); break;
        default: sprintf(result, "%s, %s and %d others like this", names[0], names[1], n - 2); break;
    }
}

int main() {
    char result[100];
    char *names[] = {};
    likes(names, 0, result);
    printf("%s\n", result);

    char *names1[] = {"Peter"};
    likes(names1, 1, result);
    printf("%s\n", result);

    char *names2[] = {"Jacob", "Alex"};
    likes(names2, 2, result);
    printf("%s\n", result);

    char *names3[] = {"Max", "John", "Mark"};
    likes(names3, 3, result);
    printf("%s\n", result);

    char *names4[] = {"Alex", "Jacob", "Mark", "Max"};
    likes(names4, 4, result);
    printf("%s\n", result);

    return 0;
}