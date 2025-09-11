#include <stdio.h>
#include <string.h>
#include <stdarg.h>

char* who_likes_it(int count, ...) {
    static char buffer[256];
    va_list names;
    va_start(names, count);

    if (count == 0) {
        strcpy(buffer, "no one likes this");
    } else if (count == 1) {
        sprintf(buffer, "%s likes this", va_arg(names, char*));
    } else if (count == 2) {
        char* name1 = va_arg(names, char*);
        char* name2 = va_arg(names, char*);
        sprintf(buffer, "%s and %s like this", name1, name2);
    } else if (count == 3) {
        char* name1 = va_arg(names, char*);
        char* name2 = va_arg(names, char*);
        char* name3 = va_arg(names, char*);
        sprintf(buffer, "%s, %s and %s like this", name1, name2, name3);
    } else {
        char* name1 = va_arg(names, char*);
        char* name2 = va_arg(names, char*);
        sprintf(buffer, "%s, %s and %d others like this", name1, name2, count - 2);
    }

    va_end(names);
    return buffer;
}

int main() {
    printf("%s\n", who_likes_it(0));
    printf("%s\n", who_likes_it(1, "Peter"));
    printf("%s\n", who_likes_it(2, "Jacob", "Alex"));
    printf("%s\n", who_likes_it(3, "Max", "John", "Mark"));
    printf("%s\n", who_likes_it(4, "Alex", "Jacob", "Mark", "Max"));
    return 0;
}