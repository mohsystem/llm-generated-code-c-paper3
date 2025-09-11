#include <stdio.h>
#include <stdlib.h>

void displayLikes(const char *names[], int size) {
    if (size == 0) {
        printf("no one likes this\n");
    } else if (size == 1) {
        printf("%s likes this\n", names[0]);
    } else if (size == 2) {
        printf("%s and %s like this\n", names[0], names[1]);
    } else if (size == 3) {
        printf("%s, %s and %s like this\n", names[0], names[1], names[2]);
    } else {
        printf("%s, %s and %d others like this\n", names[0], names[1], size - 2);
    }
}

int main() {
    const char *empty[] = {};
    displayLikes(empty, 0);

    const char *single[] = {"Peter"};
    displayLikes(single, 1);

    const char *pair[] = {"Jacob", "Alex"};
    displayLikes(pair, 2);

    const char *triple[] = {"Max", "John", "Mark"};
    displayLikes(triple, 3);

    const char *quad[] = {"Alex", "Jacob", "Mark", "Max"};
    displayLikes(quad, 4);

    return 0;
}