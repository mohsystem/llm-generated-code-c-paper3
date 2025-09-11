#include <stdio.h>
#include <string.h>
#include <regex.h>

int isValidIP(const char *ip) {
    regex_t regex;
    int reti;

    reti = regcomp(&regex, "^([0-9]{1,3}\\.){3}[0-9]{1,3}$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 0;
    }

    reti = regexec(&regex, ip, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
        int parts[4];
        sscanf(ip, "%d.%d.%d.%d", &parts[0], &parts[1], &parts[2], &parts[3]);
        for (int i = 0; i < 4; i++) {
            if (parts[i] < 0 || parts[i] > 255) {
                return 0;
            }
        }
        return 1;
    }
    
    return 0;
}

int main() {
    printf("%d\n", isValidIP("0.0.0.0")); // 1 (true)
    printf("%d\n", isValidIP("255.255.255.255")); // 1 (true)
    printf("%d\n", isValidIP("1.2.3.4")); // 1 (true)
    printf("%d\n", isValidIP("1.2.3.4.5")); // 0 (false)
    printf("%d\n", isValidIP("256.1.2.3")); // 0 (false)
    return 0;
}