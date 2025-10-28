// C does not have native JNDI support as it's a Java-specific API
// This is a basic simulation using string validation

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_NAME_LENGTH 256
#define MAX_REGISTRY_SIZE 100

typedef struct {
    char name[MAX_NAME_LENGTH];
    void* resource;
    int is_used;
} RegistryEntry;

typedef struct {
    RegistryEntry entries[MAX_REGISTRY_SIZE];
    int count;
} LocalRegistry;

LocalRegistry globalRegistry = {0};

// Check if string starts with a prefix
int starts_with(const char* str, const char* prefix) {
    if (!str || !prefix) return 0;
    size_t len_prefix = strlen(prefix);
    size_t len_str = strlen(str);
    if (len_str < len_prefix) return 0;
    return strncmp(str, prefix, len_prefix) == 0;
}

// Check if string is empty or whitespace only
int is_empty_or_whitespace(const char* str) {
    if (!str || strlen(str) == 0) return 1;
    while (*str) {
        if (!isspace((unsigned char)*str)) return 0;
        str++;
    }
    return 1;
}

// Check if JNDI name uses dangerous protocol
int is_dangerous_protocol(const char* jndi_name) {
    if (!jndi_name) return 1;

    if (starts_with(jndi_name, "ldap://") ||
        starts_with(jndi_name, "LDAP://") ||
        starts_with(jndi_name, "rmi://")  ||
        starts_with(jndi_name, "RMI://")  ||
        starts_with(jndi_name, "dns://")  ||
        starts_with(jndi_name, "DNS://")  ||
        starts_with(jndi_name, "iiop://") ||
        starts_with(jndi_name, "IIOP://")) {
        return 1;
    }
    return 0;
}

// Secure JNDI lookup simulation
void* perform_jndi_lookup(const char* jndi_name) {
    // Input validation
    if (is_empty_or_whitespace(jndi_name)) {
        fprintf(stderr, "Error: JNDI name cannot be null or empty\n");
        return NULL;
    }

    // Whitelist validation - block remote protocols
    if (is_dangerous_protocol(jndi_name)) {
        fprintf(stderr, "Security Error: Remote JNDI lookups are not allowed for security reasons\n");
        return NULL;
    }

    // Only allow java: namespace
    if (!starts_with(jndi_name, "java:")) {
        fprintf(stderr, "Security Error: Only java: namespace is allowed\n");
        return NULL;
    }

    // Search in local registry
    for (int i = 0; i < globalRegistry.count; i++) {
        if (globalRegistry.entries[i].is_used &&
            strcmp(globalRegistry.entries[i].name, jndi_name) == 0) {
            printf("Successfully retrieved resource: %s\n", jndi_name);
            return globalRegistry.entries[i].resource;
        }
    }

    printf("Resource not found: %s\n", jndi_name);
    return NULL;
}

// Bind resource to registry
int bind_resource(const char* jndi_name, void* resource) {
    if (is_empty_or_whitespace(jndi_name) || !starts_with(jndi_name, "java:")) {
        fprintf(stderr, "Security Error: Can only bind to java: namespace\n");
        return -1;
    }

    if (globalRegistry.count >= MAX_REGISTRY_SIZE) {
        fprintf(stderr, "Error: Registry is full\n");
        return -1;
    }

    strncpy(globalRegistry.entries[globalRegistry.count].name, jndi_name, MAX_NAME_LENGTH - 1);
    globalRegistry.entries[globalRegistry.count].name[MAX_NAME_LENGTH - 1] = '\0';
    globalRegistry.entries[globalRegistry.count].resource = resource;
    globalRegistry.entries[globalRegistry.count].is_used = 1;
    globalRegistry.count++;

    printf("Successfully bound resource: %s\n", jndi_name);
    return 0;
}

int main() {
    printf("=== JNDI Lookup Security Demo (C Simulation) ===\n\n");

    // Bind a test resource
    char test_data[] = "TestDatabase";
    bind_resource("java:comp/env/example", test_data);
    printf("\n");

    // Test Case 1: Valid local lookup
    printf("Test Case 1: Valid local java: namespace lookup\n");
    void* result1 = perform_jndi_lookup("java:comp/env/example");
    printf("Result: %s\n\n", result1 ? "Found" : "Not found");

    // Test Case 2: Attempting LDAP lookup (should be blocked)
    printf("Test Case 2: Blocked LDAP lookup attempt\n");
    void* result2 = perform_jndi_lookup("ldap://malicious.com/exploit");
    (void)result2;
    printf("\n");

    // Test Case 3: Attempting RMI lookup (should be blocked)
    printf("Test Case 3: Blocked RMI lookup attempt\n");
    void* result3 = perform_jndi_lookup("rmi://malicious.com/exploit");
    (void)result3;
    printf("\n");

    // Test Case 4: NULL JNDI name
    printf("Test Case 4: NULL JNDI name validation\n");
    void* result4 = perform_jndi_lookup(NULL);
    (void)result4;
    printf("\n");

    // Test Case 5: Empty JNDI name
    printf("Test Case 5: Empty JNDI name validation\n");
    void* result5 = perform_jndi_lookup("");
    (void)result5;
    printf("\n");

    printf("=== Security Summary ===\n");
    printf("✓ Remote lookups (LDAP, RMI, DNS, IIOP) are blocked\n");
    printf("✓ Only local java: namespace is allowed\n");
    printf("✓ Input validation prevents injection attacks\n");
    printf("✓ Proper error handling\n");

    return 0;
}
