#include <stdio.h>
#include <string.h>
#include <stdarg.h>

char* whoLikesIt(int count, ...) {
    static char buffer[256];
    va_list names;
    va_start(names, count);

    switch (count) {
        case 0:
            strcpy(buffer, "no one likes this");
            break;
        case 1:
            snprintf(buffer, sizeof(buffer), "%s likes this", va_arg(names, char*));
            break;
        case 2:
            snprintf(buffer, sizeof(buffer), "%s and %s like this", va_arg(names, char*), va_arg(names, char*));
            break;
        case 3:
            snprintf(buffer, sizeof(buffer), "%s, %s and %s like this", va_arg(names, char*), va_arg(names, char*), va_arg(names, char*));
            break;
        default:
            char *name1 = va_arg(names, char*);
            char *name2 = va_arg(names, char*);
            snprintf(buffer, sizeof(buffer), "%s, %s and %d others like this", name1, name2, count - 2);
            break;
    }

    va_end(names);
    return buffer;
}

int main() {
    printf("%s\n", whoLikesIt(0));
    printf("%s\n", whoLikesIt(1, "Peter"));
    printf("%s\n", whoLikesIt(2, "Jacob", "Alex"));
    printf("%s\n", whoLikesIt(3, "Max", "John", "Mark"));
    printf("%s\n", whoLikesIt(4, "Alex", "Jacob", "Mark", "Max"));
    return 0;
}