
#include <stdio.h>
#include <string.h>

const char* getRedirectPage(int choice) {
    switch(choice) {
        case 1:
            return "home.html";
        case 2:
            return "about.html";
        case 3:
            return "contact.html";
        case 4:
            return "products.html";
        default:
            return "404.html";
    }
}

int main() {
    // Test cases
    printf("%s\\n", getRedirectPage(1)); // Should print home.html
    printf("%s\\n", getRedirectPage(2)); // Should print about.html
    printf("%s\\n", getRedirectPage(3)); // Should print contact.html
    printf("%s\\n", getRedirectPage(4)); // Should print products.html
    printf("%s\\n", getRedirectPage(5)); // Should print 404.html
    return 0;
}
