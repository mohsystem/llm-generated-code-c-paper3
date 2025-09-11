#include <stdio.h>
#include <string.h>
#include <stdarg.h>

// Function to concatenate strings with formatting
char* concat(const char *format, ...) {
    char *buffer = (char *) malloc(1024); // Allocate sufficient memory
    if (buffer == NULL) return NULL; // Handle memory allocation failure
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, 1024, format, args);
    va_end(args);
    return buffer; // Return the concatenated string
}

char* who_likes_it(int count, ...) {
    va_list names;
    va_start(names, count);
    char* result;

    switch (count) {
        case 0:
            result = concat("no one likes this");
            break;
        case 1:
            result = concat("%s likes this", va_arg(names, char*));
            break;
        case 2:
            result = concat("%s and %s like this", va_arg(names, char*), va_arg(names, char*));
            break;
        case 3:
            result = concat("%s, %s and %s like this", va_arg(names, char*), va_arg(names, char*), va_arg(names, char*));
            break;
        default:
            char* name1 = va_arg(names, char*);
            char* name2 = va_arg(names, char*);
            result = concat("%s, %s and %d others like this", name1, name2, count - 2);
            break;
    }
    va_end(names);
    return result;
}

int main() {
    char *test1 = who_likes_it(0);
    printf("%s\n", test1);
    free(test1); // Free allocated memory

    char *test2 = who_likes_it(1, "Peter");
    printf("%s\n", test2);
    free(test2);

    char *test3 = who_likes_it(2, "Jacob", "Alex");
    printf("%s\n", test3);
    free(test3);

    char *test4 = who_likes_it(3, "Max", "John", "Mark");
    printf("%s\n", test4);
    free(test4);
    
    char *test5 = who_likes_it(4, "Alex", "Jacob", "Mark", "Max");
    printf("%s\n", test5);
    free(test5);

    return 0;
}