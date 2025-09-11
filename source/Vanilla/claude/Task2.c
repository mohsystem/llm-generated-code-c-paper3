
#include <stdio.h>

void createPhoneNumber(const int arr[10], char *buff) {
    sprintf(buff, "(%d%d%d) %d%d%d-%d%d%d%d", 
            arr[0], arr[1], arr[2], arr[3], arr[4], 
            arr[5], arr[6], arr[7], arr[8], arr[9]);
}

int main() {
    char phoneNumber[15];
    int test1[] = {1,2,3,4,5,6,7,8,9,0};
    int test2[] = {9,9,9,8,8,8,7,7,7,6};
    int test3[] = {0,1,2,3,4,5,6,7,8,9};
    int test4[] = {1,1,1,2,2,2,3,3,3,4};
    int test5[] = {5,5,5,4,4,4,3,3,3,2};
    
    createPhoneNumber(test1, phoneNumber);
    printf("%s\\n", phoneNumber);
    createPhoneNumber(test2, phoneNumber);
    printf("%s\\n", phoneNumber);
    createPhoneNumber(test3, phoneNumber);
    printf("%s\\n", phoneNumber);
    createPhoneNumber(test4, phoneNumber);
    printf("%s\\n", phoneNumber);
    createPhoneNumber(test5, phoneNumber);
    printf("%s\\n", phoneNumber);
    
    return 0;
}
