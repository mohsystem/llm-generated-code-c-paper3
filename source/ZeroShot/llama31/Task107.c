// Note: This example requires an LDAP library like OpenLDAP.
// Here is a simplified example using the OpenLDAP library.

#include <ldap.h>
#include <stdio.h>

int main() {
    LDAP *ld;
    int rc;
    char *server = "localhost";
    int port = 389;
    char *base_dn = "ou=people,dc=example,dc=com";
    char *filter = "(objectClass=*)";

    ld = ldap_init(server, port);
    if (ld == NULL) {
        perror("ldap_init");
        return 1;
    }

    rc = ldap_bind_s(ld, NULL, NULL, LDAP_AUTH_SIMPLE);
    if (rc != LDAP_SUCCESS) {
        ldap_perror(ld, "ldap_bind_s");
        ldap_unbind_ext_s(ld, NULL, NULL);
        return 1;
    }

    LDAPMessage *result;
    rc = ldap_search_ext_s(ld, base_dn, LDAP_SCOPE_SUBTREE, filter, NULL, 0, NULL, NULL, NULL, 0, &result);
    if (rc != LDAP_SUCCESS) {
        ldap_perror(ld, "ldap_search_ext_s");
        ldap_unbind_ext_s(ld, NULL, NULL);
        return 1;
    }

    for (LDAPMessage *entry = ldap_first_entry(ld, result); entry != NULL; entry = ldap_next_entry(ld, entry)) {
        BerElement *ber;
        char *dn;
        dn = ldap_get_dn(ld, entry);
        printf("Lookup result: %s\n", dn);
        ldap_memfree(dn);
    }

    ldap_msgfree(result);
    ldap_unbind_ext_s(ld, NULL, NULL);

    return 0;
}