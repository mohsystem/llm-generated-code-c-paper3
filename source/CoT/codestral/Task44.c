#include<stdio.h>

int square(int num) {
    return num * num;
}

int main() {
    int num;
    printf("Enter a number: ");
    if (scanf("%d", &num) == 1) {
        printf("Square of the number is: %d\n", square(num));
    } else {
        printf("Invalid input. Please enter a number.\n");
    }
    return 0;
}