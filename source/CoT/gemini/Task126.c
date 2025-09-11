#include <stdio.h>
#include <string.h>
#include <ctype.h>

// A simplified version for C since it doesn't have built-in hash maps
const char* redirect(const char* input) {
    char lower_input[100]; // Make sure this is large enough for your input

    // Convert input to lowercase
    strcpy(lower_input, input);
    for (int i = 0; lower_input[i]; i++) {
        lower_input[i] = tolower(lower_input[i]);
    }


    if (strcmp(lower_input, "home") == 0) {
        return "/home";
    } else if (strcmp(lower_input, "about") == 0) {
        return "/about";
    } else if (strcmp(lower_input, "contact") == 0) {
        return "/contact";
    } else if (strcmp(lower_input, "products") == 0) {
        return "/products";
    } else {
        return "/error";
    }
}

int main() {
    char input[100];

    printf("Enter your choice (home, about, contact, products): ");
    scanf("%s", input);  // Use %s to read a string; be mindful of buffer overflows

    const char* redirectedUrl = redirect(input);
    printf("Redirecting to: %s\n", redirectedUrl);


    // Test cases
    printf("%s\n", redirect("home"));  // /home
    printf("%s\n", redirect("About"));  // /about
    printf("%s\n", redirect("invalid")); // /error
    printf("%s\n", redirect("PRODUCTS")); // /products
    printf("%s\n", redirect("contact")); // /contact

    return 0;
}