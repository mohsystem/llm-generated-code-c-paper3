#include <stdio.h>
#include <regex.h>

bool isValidURL(const char* url) {
    // Regex to check valid URL
    const char* regex = "((http|https)://)(www.)?[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)";
    regex_t regexCompiled;
    int reti = regcomp(&regexCompiled, regex, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return false;
    }

    int ret = regexec(&regexCompiled, url, 0, NULL, 0);
    regfree(&regexCompiled);
    return ret == 0;
}

int main() {
    const char* testCases[] = {
        "https://www.geeksforgeeks.org",
        "https:// www.geeksforgeeks.org/", // Invalid due to space
        "http://example.com",
        "http://example.com/path",
        "https://example.com/path?query=param"
    };

    for (int i = 0; i < 5; ++i) {
        if (isValidURL(testCases[i])) {
            printf("Yes, the URL is valid: %s\n", testCases[i]);
        } else {
            printf("No, the URL is not valid: %s\n", testCases[i]);
        }
    }

    return 0;
}