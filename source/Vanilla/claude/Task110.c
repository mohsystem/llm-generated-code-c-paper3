
#include <stdio.h>
#include <string.h>
#include <regex.h>

int isValidURL(const char* url) {
    regex_t regex;
    int result;
    
    // Compile regular expression
    result = regcomp(&regex, "^(https?://)?([[:alnum:]-]+\\\\.)+[[:alnum:]-]+(/[[:alnum:]- ./?%&=]*)?$", REG_EXTENDED);
    
    if (result) {
        return 0;  // Compilation failed
    }
    
    // Execute regular expression
    result = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);
    
    return result == 0;
}

int main() {
    const char* urls[] = {
        "https://www.example.com",
        "http://subdomain.example.co.uk/path",
        "invalid url",
        "ftp://invalid.com",
        "https://valid-url.com/path?param=value"
    };
    
    for(int i = 0; i < 5; i++) {
        printf("URL: %s is %s\\n", urls[i], isValidURL(urls[i]) ? "valid" : "invalid");
    }
    
    return 0;
}
