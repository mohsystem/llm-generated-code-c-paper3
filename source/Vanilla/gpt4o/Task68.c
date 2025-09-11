#include <stdio.h>
#include <stdlib.h>
#include <ldap.h>

char* ldap_search(const char* dc, const char* username) {
    LDAP *ld;
    LDAPMessage *result, *entry;
    char *dn;
    int rc;
    static char result_string[256];

    char ldap_uri[] = "ldap://localhost:389";
    char search_base[256];
    snprintf(search_base, sizeof(search_base), "dc=%s,dc=com", dc);
    char search_filter[256];
    snprintf(search_filter, sizeof(search_filter), "(uid=%s)", username);

    rc = ldap_initialize(&ld, ldap_uri);
    if (rc != LDAP_SUCCESS) {
        return "Failed to initialize LDAP";
    }

    rc = ldap_simple_bind_s(ld, NULL, NULL);
    if (rc != LDAP_SUCCESS) {
        ldap_unbind_ext_s(ld, NULL, NULL);
        return "Failed to bind LDAP";
    }

    rc = ldap_search_ext_s(ld, search_base, LDAP_SCOPE_SUBTREE, search_filter, NULL, 0, NULL, NULL, NULL, 0, &result);
    if (rc != LDAP_SUCCESS) {
        ldap_unbind_ext_s(ld, NULL, NULL);
        return "User not found";
    }

    entry = ldap_first_entry(ld, result);
    if (entry != NULL) {
        dn = ldap_get_dn(ld, entry);
        snprintf(result_string, sizeof(result_string), "%s", dn);
        ldap_memfree(dn);
        ldap_msgfree(result);
        ldap_unbind_ext_s(ld, NULL, NULL);
        return result_string;
    }

    ldap_msgfree(result);
    ldap_unbind_ext_s(ld, NULL, NULL);
    return "User not found";
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Please provide domain component and username.\n");
        return 1;
    }
    const char* dc = argv[1];
    const char* username = argv[2];
    printf("%s\n", ldap_search(dc, username));
    return 0;
}