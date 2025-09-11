#include <stdio.h>
#include <string.h>
#include <ldap.h>

char* escapeLdapSearchFilter(const char* filter) {
    static char escaped[256];
    int i, j = 0;
    for (i = 0; filter[i] != '\0'; i++) {
        switch (filter[i]) {
            case '\\':
                strcat(escaped + j, "\\5c");
                j += 3;
                break;
            case '*':
                strcat(escaped + j, "\\2a");
                j += 3;
                break;
            case '(':
                strcat(escaped + j, "\\28");
                j += 3;
                break;
            case ')':
                strcat(escaped + j, "\\29");
                j += 3;
                break;
            case '\0':
                strcat(escaped + j, "\\00");
                j += 3;
                break;
            default:
                escaped[j++] = filter[i];
        }
    }
    escaped[j] = '\0';
    return escaped;
}

char* searchLdap(const char* domainComponent, const char* username) {
    LDAP *ld;
    LDAPMessage *result, *entry;
    char *attrs[] = {NULL};
    int rc;
    
    char filter[256];
    snprintf(filter, sizeof(filter), "(&(objectClass=person)(uid=%s))", escapeLdapSearchFilter(username));

    char searchBase[256];
    snprintf(searchBase, sizeof(searchBase), "dc=%s,dc=com", escapeLdapSearchFilter(domainComponent));

    rc = ldap_initialize(&ld, "ldap://localhost:389");
    if (rc != LDAP_SUCCESS) {
        return "";
    }

    rc = ldap_search_ext_s(ld, searchBase, LDAP_SCOPE_SUBTREE, filter, attrs, 0, NULL, NULL, NULL, LDAP_NO_LIMIT, &result);
    if (rc != LDAP_SUCCESS) {
        ldap_unbind_ext_s(ld, NULL, NULL);
        return "";
    }

    entry = ldap_first_entry(ld, result);
    if (entry != NULL) {
        char* dn = ldap_get_dn(ld, entry);
        ldap_msgfree(result);
        ldap_unbind_ext_s(ld, NULL, NULL);
        return dn;
    }

    ldap_msgfree(result);
    ldap_unbind_ext_s(ld, NULL, NULL);
    return "";
}

int main() {
    printf("%s\n", searchLdap("example", "john.doe"));
    printf("%s\n", searchLdap("example", "jane.smith"));
    printf("%s\n", searchLdap("example", "bob.jones"));
    printf("%s\n", searchLdap("example", "alice.brown"));
    printf("%s\n", searchLdap("example", "charlie.black"));
    return 0;
}