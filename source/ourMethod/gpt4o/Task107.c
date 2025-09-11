#include <stdio.h>
#include <string.h>

void performJNDILookup(const char* jndiName, char* result, size_t resultSize) {
    if (resultSize > 0) {
        // Simulate JNDI lookup
        snprintf(result, resultSize, "Resource for %s", jndiName);
    } else {
        fprintf(stderr, "Result buffer size is too small\n");
    }
}

int main() {
    char result1[256];
    char result2[256];
    char result3[256];
    char result4[256];
    char result5[256];

    // Test cases
    performJNDILookup("java:comp/env/jdbc/DataSource1", result1, sizeof(result1));
    performJNDILookup("java:comp/env/jdbc/DataSource2", result2, sizeof(result2));
    performJNDILookup("java:comp/env/jdbc/Invalid", result3, sizeof(result3));
    performJNDILookup("java:comp/env/jdbc/DataSource3", result4, sizeof(result4));
    performJNDILookup("java:comp/env/jdbc/DataSource4", result5, sizeof(result5));

    printf("%s\n", result1);
    printf("%s\n", result2);
    printf("%s\n", result3);
    printf("%s\n", result4);
    printf("%s\n", result5);

    return 0;
}