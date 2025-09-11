
#include <stdio.h>
#include <string.h>

char* createPhoneNumber(const int arr[10], char *buff) {
    if (arr == NULL || buff == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < 10; i++) {
        if (arr[i] < 0 || arr[i] > 9) {
            return NULL;
        }
    }
    
    sprintf(buff, "(%d%d%d) %d%d%d-%d%d%d%d",
            arr[0], arr[1], arr[2], arr[3], arr[4],
            arr[5], arr[6], arr[7], arr[8], arr[9]);
            
    return buff;
}

int main() {
    char buffer[15];
    
    // Test cases
    int test1[] = {1,2,3,4,5,6,7,8,9,0};
    int test2[] = {9,9,9,8,8,8,7,7,7,6};
    int test3[] = {0,1,2,3,4,5,6,7,8,9};
    int test4[] = {5,5,5,4,4,4,3,3,3,2};
    int test5[] = {1,1,1,1,1,1,1,1,1,1};
    
    printf("%s\\n", createPhoneNumber(test1, buffer));
    printf("%s\\n", createPhoneNumber(test2, buffer));
    printf("%s\\n", createPhoneNumber(test3, buffer));
    printf("%s\\n", createPhoneNumber(test4, buffer));
    printf("%s\\n", createPhoneNumber(test5, buffer));
    
    return 0;
}
