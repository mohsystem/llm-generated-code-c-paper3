#include <stdio.h>
#include <stdlib.h>

void likes(int n, char *names[]) {
    switch (n) {
        case 0: printf("no one likes this\n"); break;
        case 1: printf("%s likes this\n", names[0]); break;
        case 2: printf("%s and %s like this\n", names[0], names[1]); break;
        case 3: printf("%s, %s and %s like this\n", names[0], names[1], names[2]); break;
        default: printf("%s, %s and %d others like this\n", names[0], names[1], n - 2); break;
    }
}

int main() {
    char *noOne[] = {};
    char *peter[] = {"Peter"};
    char *jacobAlex[] = {"Jacob", "Alex"};
    char *maxJohnMark[] = {"Max", "John", "Mark"};
    char *alexJacobMarkMax[] = {"Alex", "Jacob", "Mark", "Max"};

    likes(0, noOne);
    likes(1, peter);
    likes(2, jacobAlex);
    likes(3, maxJohnMark);
    likes(4, alexJacobMarkMax);

    return 0;
}