
#include <stdio.h>
#include <string.h>
#include <ldap.h>
#include <stdlib.h>

char* construct_search_base(const char* domain) {
    char* result = malloc(strlen(domain) * 2 + 10);
    char* temp = strdup(domain);
    char* token;
    result[0] = '\\0';
    
    token = strtok(temp, ".");
    while (token != NULL) {
        strcat(result, "dc=");
        strcat(result, token);
        token = strtok(NULL, ".");
        if (token != NULL) {
            strcat(result, ",");
        }
    }
    
    free(temp);
    return result;
}

char* search_ldap(const char* username, const char* domain) {
    LDAP* ld;
    int rc;
    char* result = malloc(256);
    
    // Initialize LDAP connection
    rc = ldap_initialize(&ld, "ldap://localhost:389");
    if (rc != LDAP_SUCCESS) {
        sprintf(result, "Error: Could not initialize LDAP connection");
        return result;
    }
    
    // Construct search base and filter
    char* search_base = construct_search_base(domain);
    char search_filter[100];
    sprintf(search_filter, "(&(objectClass=person)(uid=%s))", username);
    
    // Set search parameters
    char* attrs[] = {"cn", "mail", NULL};
    LDAPMessage* res;
    
    // Perform search
    rc = ldap_search_ext_s(
        ld,
        search_base,
        LDAP_SCOPE_SUBTREE,
        search_filter,
        attrs,
        0,
        NULL,
        NULL,
        NULL,
        0,
        &res
    );
    
    if (rc != LDAP_SUCCESS) {
        sprintf(result, "Error: Search failed");
        free(search_base);
        ldap_unbind_ext_s(ld, NULL, NULL);
        return result;
    }
    
    // Process results
    if (ldap_count_entries(ld, res) > 0) {
        LDAPMessage* entry = ldap_first_entry(ld, res);
        char* cn = ldap_get_values(ld, entry, "cn")[0];
        char* mail = ldap_get_values(ld, entry, "mail")[0];
        sprintf(result, "User found: %s, %s", cn, mail);
    } else {
        sprintf(result, "User not found");
    }
    
    free(search_base);
    ldap_msgfree(res);
    ldap_unbind_ext_s(ld, NULL, NULL);
    return result;
}

int main() {
    // Test cases
    printf("%s\\n", search_ldap("john.doe", "example.com"));
    printf("%s\\n", search_ldap("jane.smith", "company.org"));
    printf("%s\\n", search_ldap("admin", "local.net"));
    printf("%s\\n", search_ldap("user1", "test.com"));
    printf("%s\\n", search_ldap("guest", "domain.com"));
    
    return 0;
}
