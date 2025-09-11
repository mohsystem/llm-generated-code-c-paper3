#include <stdio.h>
#include <stdlib.h>

int square(int num) {
    return num * num;
}

int main() {
    for (int i = 0; i < 5; i++) {
        int input;
        while (true) {
            printf("Enter an integer: ");
            if (scanf("%d", &input) == 1) {
                int result = square(input);
                printf("The square of %d is %d\n", input, result);
                break;
            } else {
                printf("Invalid input. Please enter an integer.\n");
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
            }
        }
    }
    return 0;
}