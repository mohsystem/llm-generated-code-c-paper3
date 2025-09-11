#include <stdio.h>
#include <string.h>
#include <ctype.h>

int validatedIntegerInput() {
    int input;
    while (1) {
        if (scanf("%d", &input) == 1) {
            break;
        } else {
            printf("Invalid input. Please enter an integer.\n");
            while (getchar() != '\n'); // Clear the invalid input
        }
    }
    return input;
}

void validatedStringInput(char *input) {
    while (1) {
        scanf("%s", input);
        int valid = 1;
        for (int i = 0; input[i] != '\0'; i++) {
            if (!isalnum(input[i])) {
                valid = 0;
                break;
            }
        }
        if (valid) {
            break;
        } else {
            printf("Invalid input. Please enter alphanumeric characters only.\n");
        }
    }
}

void test(int num1, int num2, char *str) {
    printf("Test case: num1=%d, num2=%d, str=%s\n", num1, num2, str);
    printf("Expected Sum: %d\n", num1 + num2);
    printf("String: %s\n", str);
}



int main() {
    int num1, num2;
    char str[100]; // Adjust size as needed

    printf("Enter an integer:\n");
    num1 = validatedIntegerInput();

    printf("Enter another integer:\n");
    num2 = validatedIntegerInput();

    printf("Enter a string (alphanumeric characters only):\n");
    validatedStringInput(str);

    printf("Sum: %d\n", num1 + num2);
    printf("String: %s\n", str);



    test(10, 20, "hello");
    test(5, 15, "world");
    test(-5, 5, "test1");
    test(100, 200, "test2");
    test(0, 0, "test3");


    return 0;
}