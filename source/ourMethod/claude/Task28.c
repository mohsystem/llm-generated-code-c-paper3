
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 100
#define MAX_RESULT_LENGTH 256

char* who_likes_it(const char** names, int count) {
    char* result = (char*)malloc(MAX_RESULT_LENGTH);
    if (result == NULL) {
        return NULL;
    }
    
    if (count == 0 || names == NULL) {
        strncpy(result, "no one likes this", MAX_RESULT_LENGTH - 1);
    }
    else if (count == 1) {
        snprintf(result, MAX_RESULT_LENGTH - 1, "%s likes this", names[0]);
    }
    else if (count == 2) {
        snprintf(result, MAX_RESULT_LENGTH - 1, "%s and %s like this", 
                names[0], names[1]);
    }
    else if (count == 3) {
        snprintf(result, MAX_RESULT_LENGTH - 1, "%s, %s and %s like this", 
                names[0], names[1], names[2]);
    }
    else {
        snprintf(result, MAX_RESULT_LENGTH - 1, "%s, %s and %d others like this", 
                names[0], names[1], count - 2);
    }
    
    result[MAX_RESULT_LENGTH - 1] = '\\0';
    return result;
}

int main() {
    // Test cases
    const char* test1[] = {};
    const char* test2[] = {"Peter"};
    const char* test3[] = {"Jacob", "Alex"};
    const char* test4[] = {"Max", "John", "Mark"};
    const char* test5[] = {"Alex", "Jacob", "Mark", "Max"};

    char* result;
    
    result = who_likes_it(test1, 0);
    printf("%s\\n", result);
    free(result);

    result = who_likes_it(test2, 1);
    printf("%s\\n", result);
    free(result);

    result = who_likes_it(test3, 2);
    printf("%s\\n", result);
    free(result);

    result = who_likes_it(test4, 3);
    printf("%s\\n", result);
    free(result);

    result = who_likes_it(test5, 4);
    printf("%s\\n", result);
    free(result);

    return 0;
}
