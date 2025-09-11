#include <stdio.h>
#include <string.h>

void expandedForm(int num, char* buffer, size_t buffer_size) {
    char parts[50][12]; // Array of string parts
    int part_count = 0;
    int factor = 1;

    while (num > 0) {
        int remainder = num % 10;
        if (remainder != 0) {
            snprintf(parts[part_count++], 12, "%d", remainder * factor);
        }
        num /= 10;
        factor *= 10;
    }

    // Building the final result
    buffer[0] = '\0';
    for (int i = part_count - 1; i >= 0; i--) {
        strncat(buffer, parts[i], buffer_size - strlen(buffer) - 1);
        if (i > 0) {
            strncat(buffer, " + ", buffer_size - strlen(buffer) - 1);
        }
    }
}

int main() {
    char result[100];

    expandedForm(12, result, 100);
    printf("%s\n", result); // Should return "10 + 2"

    expandedForm(42, result, 100);
    printf("%s\n", result); // Should return "40 + 2"

    expandedForm(70304, result, 100);
    printf("%s\n", result); // Should return "70000 + 300 + 4"

    expandedForm(807, result, 100);
    printf("%s\n", result); // Should return "800 + 7"

    expandedForm(530, result, 100);
    printf("%s\n", result); // Should return "500 + 30"

    return 0;
}