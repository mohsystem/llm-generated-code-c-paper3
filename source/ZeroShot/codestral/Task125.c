#include<stdio.h>

#define MAX_RESOURCES 3

char *resources[MAX_RESOURCES] = {"Resource1", "Resource2", "Resource3"};
int roles[MAX_RESOURCES] = {1, 2, 1};

char* accessResource(int userRole, int resourceIndex) {
    if(resourceIndex >= 0 && resourceIndex < MAX_RESOURCES) {
        if(userRole == roles[resourceIndex]) {
            return resources[resourceIndex];
        } else {
            return "Access Denied";
        }
    } else {
        return "Resource Not Found";
    }
}

int main() {
    printf("%s\n", accessResource(1, 0));  // "Resource1"
    printf("%s\n", accessResource(2, 1));  // "Resource2"
    printf("%s\n", accessResource(1, 1));  // "Access Denied"
    printf("%s\n", accessResource(1, 3));  // "Resource Not Found"
    printf("%s\n", accessResource(2, -1));  // "Resource Not Found"
    return 0;
}