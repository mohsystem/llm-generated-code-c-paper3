#include <stdio.h>
#include <string.h>

void mainFunction() {
    char* result = likes(NULL, 0);
    printf("%s\n", result); free(result); // "no one likes this"

    char* names1[] = {"Peter"};
    result = likes(names1, 1);
    printf("%s\n", result); free(result); // "Peter likes this"

    char* names2[] = {"Jacob", "Alex"};
    result = likes(names2, 2);
    printf("%s\n", result); free(result); // "Jacob and Alex like this"

    char* names3[] = {"Max", "John", "Mark"};
    result = likes(names3, 3);
    printf("%s\n", result); free(result); // "Max, John and Mark like this"

    char* names4[] = {"Alex", "Jacob", "Mark", "Max"};
    result = likes(names4, 4);
    printf("%s\n", result); free(result); // "Alex, Jacob and 2 others like this"
}

char* likes(char** names, int count) {
    char* result = malloc(1024 * sizeof(char));

    if (count == 0) {
        strcpy(result, "no one likes this");
    } else if (count == 1) {
        sprintf(result, "%s likes this", names[0]);
    } else if (count == 2) {
        sprintf(result, "%s and %s like this", names[0], names[1]);
    } else if (count == 3) {
        sprintf(result, "%s, %s and %s like this", names[0], names[1], names[2]);
    } else {
        sprintf(result, "%s, %s and %d others like this", names[0], names[1], count - 2);
    }

    return result;
}

int main() {
    mainFunction();
    return 0;
}