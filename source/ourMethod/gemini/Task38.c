#include <stdio.h>
#include <string.h>

// A very basic example (not a full web application).  C would typically 
// use a dedicated web framework (like Crow) for real web applications.
// This demonstrates the core concept for illustration.
// This example is limited and does not handle all possible scenarios or
// security considerations.
int main() {
    char user_input[200] = "";  // Limit input size to prevent buffer overflows

    printf("Enter user input: ");
    fgets(user_input, sizeof(user_input), stdin); // Safer than scanf or gets


    // Basic HTML escaping (Incomplete; a real application would need a more robust solution)
    printf("<html><body>\n");
    printf("<h1>User Input:</h1>\n");
    printf("<p>");
    for (size_t i = 0; user_input[i] != '\0'; i++) {
        switch (user_input[i]) {
            case '<':  printf("&lt;"); break;
            case '>':  printf("&gt;"); break;
            case '&':  printf("&amp;"); break;
            case '"':  printf("&quot;"); break;
            case '\'': printf("&#x27;"); break;
            case '/': printf("&#x2F;"); break;
            default:   putchar(user_input[i]);
        }
    }
    printf("</p>\n");
    printf("</body></html>\n");


    // Test cases (Illustrative - in C, a framework like Check or CUnit would be used)
    // ...
    return 0;
}