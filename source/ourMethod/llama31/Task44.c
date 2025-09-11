#include <stdio.h>
#include <stdlib.h>

int calculateSum(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    return sum;
}

int main() {
    for (int i = 0; i < 5; i++) {
        int number;
        while (true) {
            printf("Enter a number: ");
            if (scanf("%d", &number) != 1) {
                printf("Invalid input. Please enter a valid number.\n");
                // Clear input buffer
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                continue;
            }

            if (number < 0) {
                printf("Please enter a non-negative number.\n");
                continue;
            }

            break;
        }

        // Perform operation
        int sum = calculateSum(number);
        printf("The sum of numbers from 1 to %d is %d\n", number, sum);
    }

    return 0;
}