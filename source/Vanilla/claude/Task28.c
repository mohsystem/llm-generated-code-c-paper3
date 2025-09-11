
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* whoLikesIt(const char** names, int count) {
    char* result = (char*)malloc(200); // Allocate enough space for result
    
    switch(count) {
        case 0:
            strcpy(result, "no one likes this");
            break;
        case 1:
            sprintf(result, "%s likes this", names[0]);
            break;
        case 2:
            sprintf(result, "%s and %s like this", names[0], names[1]);
            break;
        case 3:
            sprintf(result, "%s, %s and %s like this", names[0], names[1], names[2]);
            break;
        default:
            sprintf(result, "%s, %s and %d others like this", names[0], names[1], count-2);
            break;
    }
    return result;
}

int main() {
    const char* test1[] = {};
    const char* test2[] = {"Peter"};
    const char* test3[] = {"Jacob", "Alex"};
    const char* test4[] = {"Max", "John", "Mark"};
    const char* test5[] = {"Alex", "Jacob", "Mark", "Max"};

    printf("%s\\n", whoLikesIt(test1, 0));
    printf("%s\\n", whoLikesIt(test2, 1));
    printf("%s\\n", whoLikesIt(test3, 2));
    printf("%s\\n", whoLikesIt(test4, 3));
    printf("%s\\n", whoLikesIt(test5, 4));

    return 0;
}
