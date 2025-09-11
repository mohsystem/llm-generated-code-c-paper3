#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isValidURL(const char *url) {
    if (strncmp(url, "http://", 7) == 0 || strncmp(url, "https://", 8) == 0) {
        return true;
    }
    return false;
}

int main() {
    const char *urls[] = {"http://example.com", "https://example.com", "ftp://example.com", "http://", "invalid"};
    for (int i = 0; i < 5; i++) {
        printf("%s is valid? %d\n", urls[i], isValidURL(urls[i]));
    }
    return 0;
}