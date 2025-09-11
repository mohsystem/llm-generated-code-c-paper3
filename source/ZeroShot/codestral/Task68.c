// C code requires an external library like openldap, which is not a standard library.
// This code may not run on all systems.
// Please replace `<your_ldap_library_path>` with your actual openldap library path.

#include <ldap.h>
#include <stdio.h>
#include <stdlib.h>

int search_user(const char* dc, const char* username) {
    LDAP* ld;
    int rc;
    char* filter;
    LDAPMessage* result;
    LDAPMessage* entry;
    char* attr;
    BerElement* ber;

    ldap_initialize(&ld, "ldap://localhost:389/");
    asprintf(&filter, "(uid=%s)", username);
    rc = ldap_search_s(ld, dc, LDAP_SCOPE_SUBTREE, filter, NULL, 0, &result);
    if (rc != LDAP_SUCCESS) {
        return rc;
    }

    for (entry = ldap_first_entry(ld, result); entry != NULL; entry = ldap_next_entry(ld, entry)) {
        for (attr = ldap_first_attribute(ld, entry, &ber); attr != NULL; attr = ldap_next_attribute(ld, entry, ber)) {
            printf("%s: %s\n", attr, ldap_get_values(ld, entry, attr)[0]);
        }
        ber_free(ber, 0);
    }

    ldap_msgfree(result);
    ldap_unbind(ld);
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <dc> <username>\n", argv[0]);
        return 1;
    }
    return search_user(argv[1], argv[2]);
}