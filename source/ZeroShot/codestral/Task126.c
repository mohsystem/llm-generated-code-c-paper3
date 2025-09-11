#include <stdio.h>
#include <string.h>

void redirectUser(char *userInput) {
    if (strcmp(userInput, "page1") == 0) {
        printf("Redirecting to page1\n");
    } else if (strcmp(userInput, "page2") == 0) {
        printf("Redirecting to page2\n");
    } else {
        printf("Redirecting to default page\n");
    }
}

int main() {
    redirectUser("page1");
    redirectUser("page2");
    redirectUser("unknown");
    return 0;
}