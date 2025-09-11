#include <stdio.h>
#include <string.h>

void whoLikesIt(char result[], const char* names[], int length) {
    switch (length) {
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
            sprintf(result, "%s, %s and %d others like this", names[0], names[1], length - 2);
            break;
    }
}

int main() {
    char result[100];
    
    const char* names1[] = {};
    whoLikesIt(result, names1, 0);
    printf("%s\n", result);
    
    const char* names2[] = {"Peter"};
    whoLikesIt(result, names2, 1);
    printf("%s\n", result);
    
    const char* names3[] = {"Jacob", "Alex"};
    whoLikesIt(result, names3, 2);
    printf("%s\n", result);
    
    const char* names4[] = {"Max", "John", "Mark"};
    whoLikesIt(result, names4, 3);
    printf("%s\n", result);
    
    const char* names5[] = {"Alex", "Jacob", "Mark", "Max"};
    whoLikesIt(result, names5, 4);
    printf("%s\n", result);
    
    return 0;
}