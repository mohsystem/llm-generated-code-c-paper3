#include <stdio.h>
#include <string.h>
#include <stdarg.h>

// Function to concatenate strings with variable arguments
char* concat(const char *str, ...) {
    va_list args;
    va_start(args, str);

    size_t len = strlen(str);
    char *buffer = (char*)malloc(len + 1); 
    strcpy(buffer, str);

    const char *arg;
    while ((arg = va_arg(args, const char *)) != NULL) {
        size_t arg_len = strlen(arg);
        buffer = (char*)realloc(buffer, len + arg_len + 1);
        strcat(buffer, arg);
        len += arg_len;
    }

    va_end(args);
    return buffer;
}


char* whoLikesIt(int count, ...) {
    va_list names;
    va_start(names, count);

    if (count == 0) {
        return "no one likes this";
    } else if (count == 1) {
        char *name = va_arg(names, char *);
        return concat(name, " likes this", NULL);
    } else if (count == 2) {
        char *name1 = va_arg(names, char *);
        char *name2 = va_arg(names, char *);
        return concat(name1, " and ", name2, " like this", NULL);
    } else if (count == 3) {
        char *name1 = va_arg(names, char *);
        char *name2 = va_arg(names, char *);
        char *name3 = va_arg(names, char *);
        return concat(name1, ", ", name2, " and ", name3, " like this", NULL);
    } else {
        char *name1 = va_arg(names, char *);
        char *name2 = va_arg(names, char *);
        char count_str[20]; // Adjust size if needed
        sprintf(count_str, "%d", count - 2);
        return concat(name1, ", ", name2, " and ", count_str, " others like this", NULL);
    }

    va_end(names);
    
}

int main() {
    printf("%s\n", whoLikesIt(0));
    printf("%s\n", whoLikesIt(1, "Peter"));
    printf("%s\n", whoLikesIt(2, "Jacob", "Alex"));
    printf("%s\n", whoLikesIt(3, "Max", "John", "Mark"));
    printf("%s\n", whoLikesIt(4, "Alex", "Jacob", "Mark", "Max"));
    return 0;
}