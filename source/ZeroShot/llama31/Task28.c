#include <stdio.h>
#include <string.h>

void likes(char *names[], int len) {
    if (len == 0) {
        printf("no one likes this\n");
    } else if (len == 1) {
        printf("%s likes this\n", names[0]);
    } else if (len == 2) {
        printf("%s and %s like this\n", names[0], names[1]);
    } else if (len == 3) {
        printf("%s, %s and %s like this\n", names[0], names[1], names[2]);
    } else {
        printf("%s, %s and %d others like this\n", names[0], names[1], len - 2);
    }
}

int main() {
    char *names1[] = {};
    char *names2[] = {"Peter"};
    char *names3[] = {"Jacob", "Alex"};
    char *names4[] = {"Max", "John", "Mark"};
    char *names5[] = {"Alex", "Jacob", "Mark", "Max"};

    likes(names1, 0);
    likes(names2, 1);
    likes(names3, 2);
    likes(names4, 3);
    likes(names5, 4);

    return 0;
}