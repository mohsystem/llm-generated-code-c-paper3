#include <stdio.h>
#include <ctype.h>

void encrypt(const char *input, char *output) {
    int key = 3; // Simple Caesar cipher shift key
    while (*input) {
        char c = *input;
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            c = (c - base + key) % 26 + base;
        }
        *output = c;
        input++;
        output++;
    }
    *output = '\0';
}

int main() {
    char output[256];
    encrypt("Hello World", output);
    printf("%s\n", output);  // Test case 1
    encrypt("Java Programming", output);
    printf("%s\n", output);  // Test case 2
    encrypt("Secure Code", output);
    printf("%s\n", output);  // Test case 3
    encrypt("Encrypt this text!", output);
    printf("%s\n", output);  // Test case 4
    encrypt("Task51 Example", output);
    printf("%s\n", output);  // Test case 5
    return 0;
}