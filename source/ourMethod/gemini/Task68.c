//Requires LDAP library. E.g., on Debian/Ubuntu: sudo apt-get install libldap2-dev -y
#include <stdio.h>
#include <ldap.h>
#include <string.h>

char* searchUser(const char* dc, const char* username) {
    LDAP *ld;
    LDAPMessage *result, *e;
    BerElement *ber;
    char *attribute;
    char **vals;
    int rc;

    char uri[100] = "ldap://localhost:389";  // LDAP URI
    char base[100];
    snprintf(base, sizeof(base), "dc=%s", dc); // Construct base DN

    char filter[100];
    snprintf(filter, sizeof(filter), "(cn=%s)", username); // Construct filter

    char *attrs[] = {"cn", "sn", "givenName", "mail", NULL};

    if (ldap_initialize(&ld, uri) != LDAP_SUCCESS) {
        return "LDAP initialization failed";  // Return error message
    }


    rc = ldap_simple_bind_s(ld, NULL, NULL); // Anonymous bind

    if (rc != LDAP_SUCCESS) {
        ldap_unbind_s(ld);
        return "LDAP bind failed";
    }

    rc = ldap_search_s(ld, base, LDAP_SCOPE_SUBTREE, filter, attrs, 0, &result);

    if (rc != LDAP_SUCCESS) {
        ldap_msgfree(result);
        ldap_unbind_s(ld);
        return "LDAP search failed";
    }


     char* userInfo = NULL;

    if ((e = ldap_first_entry(ld, result))) {
        size_t userInfoSize = 1; // Start with 1 for null terminator
        userInfo = malloc(userInfoSize);
        *userInfo = '\0'; // Initialize as empty string

        for (attribute = ldap_first_attribute(ld, e, &ber); attribute; attribute = ldap_next_attribute(ld, e, ber)) {
             if ((vals = ldap_get_values(ld, e, attribute)) != NULL) {
                for (int i = 0; vals[i]; i++) {
                    size_t attrLen = strlen(attribute);
                    size_t valueLen = strlen(vals[i]);

                    char* newUserInfo = realloc(userInfo, userInfoSize + attrLen + valueLen + 4); // +4 for ": \n\0"
                    if (newUserInfo == NULL) {
                        // Handle memory allocation failure
                        free(userInfo);
                        ldap_value_free(vals);
                        ldap_memfree(attribute);
                        ldap_msgfree(result);
                        ldap_unbind_s(ld);
                        return "Memory allocation failed";
                    }
                    userInfo = newUserInfo;
                    strcat(userInfo, attribute);
                    strcat(userInfo, ": ");
                    strcat(userInfo, vals[i]);
                    strcat(userInfo, "\n");

                    userInfoSize += attrLen + valueLen + 3; // Update size
                }

                ldap_value_free(vals);  // Free values
            }
            ldap_memfree(attribute); // Free attribute

        }
        if (ber != NULL) {
            ber_free(ber, 0);
        }
    }


    ldap_msgfree(result);
    ldap_unbind_s(ld);


    if (userInfo == NULL) {
        return "User not found";
    }
    return userInfo;
}


int main() {
    printf("Test Case 1:\n%s\n", searchUser("example,com", "testuser"));
    printf("\nTest Case 2:\n%s\n", searchUser("mydomain,org", "johnDoe"));
    printf("\nTest Case 3:\n%s\n", searchUser("example,com", "user123"));
    printf("\nTest Case 4:\n%s\n", searchUser("domain,net", "adminUser"));
    printf("\nTest Case 5:\n%s\n", searchUser("test,com", "newUser"));
    return 0;
}