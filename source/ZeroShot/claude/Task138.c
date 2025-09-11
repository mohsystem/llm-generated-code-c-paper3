
#include <stdio.h>
#include <string.h>

#define READ 4
#define WRITE 2
#define EXECUTE 1

int checkPermission(int userPermissions, int requiredPermission) {
    return (userPermissions & requiredPermission) == requiredPermission;
}

int grantPermission(int currentPermissions, int newPermission) {
    return currentPermissions | newPermission;
}

int revokePermission(int currentPermissions, int permission) {
    return currentPermissions & ~permission;
}

void getPermissionString(int permissions, char* result) {
    result[0] = (permissions & READ) ? 'r' : '-';
    result[1] = (permissions & WRITE) ? 'w' : '-';
    result[2] = (permissions & EXECUTE) ? 'x' : '-';
    result[3] = '\\0';
}

int main() {
    char permStr[4];
    
    // Test case 1: Grant read permission
    int permissions = 0;
    permissions = grantPermission(permissions, READ);
    getPermissionString(permissions, permStr);
    printf("Test 1: %s\\n", permStr);
    
    // Test case 2: Grant write and execute permissions
    permissions = grantPermission(permissions, WRITE | EXECUTE);
    getPermissionString(permissions, permStr);
    printf("Test 2: %s\\n", permStr);
    
    // Test case 3: Check for write permission
    printf("Test 3: Has write permission: %d\\n", checkPermission(permissions, WRITE));
    
    // Test case 4: Revoke write permission
    permissions = revokePermission(permissions, WRITE);
    getPermissionString(permissions, permStr);
    printf("Test 4: %s\\n", permStr);
    
    // Test case 5: Check for write permission after revocation
    printf("Test 5: Has write permission: %d\\n", checkPermission(permissions, WRITE));
    
    return 0;
}
