#include <stdio.h>
#include <ldap.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: ./task68 <domain_component> <username>\n");
        return 1;
    }

    char* domainComponent = argv[1];
    char* username = argv[2];

    char ldapUrl[100];
    sprintf(ldapUrl, "ldap://localhost:389");

    char searchBase[100];
    sprintf(searchBase, "dc=%s", domainComponent);

    char searchFilter[100];
    sprintf(searchFilter, "(&(objectClass=*)(uid=%s))", username);

    LDAP* ldap = ldap_init(ldapUrl, LDAP_VERSION3);
    if (ldap == NULL) {
        fprintf(stderr, "Error: Failed to initialize LDAP connection\n");
        return 1;
    }

    int result = ldap_simple_bind_s(ldap, NULL, NULL);
    if (result != LDAP_SUCCESS) {
        fprintf(stderr, "Error: Failed to bind to LDAP server\n");
        ldap_unbind_ext_s(ldap, NULL, NULL);
        return 1;
    }

    LDAPMessage* searchResult;
    result = ldap_search_s(ldap, searchBase, LDAP_SCOPE_SUBTREE, searchFilter, NULL, 0, &searchResult);
    if (result != LDAP_SUCCESS) {
        fprintf(stderr, "Error: Failed to search LDAP server\n");
        ldap_unbind_ext_s(ldap, NULL, NULL);
        return 1;
    }

    LDAPMessage* entry = ldap_first_entry(ldap, searchResult);
    if (entry == NULL) {
        printf("User not found.\n");
    } else {
        printf("User Information:\n");
        BerElement* ber = NULL;
        char* attributeName = ldap_first_attribute(ldap, entry, &ber);
        while (attributeName != NULL) {
            struct berval** values = ldap_get_values_len(ldap, entry, attributeName);
            if (values != NULL) {
                printf("%s: %s\n", attributeName, values[0]->bv_val);
                ldap_value_free_len(values);
            }
            attributeName = ldap_next_attribute(ldap, entry, ber);
        }
        if (ber != NULL) {
            ber_free(ber, 0);
        }
    }

    ldap_msgfree(searchResult);
    ldap_unbind_ext_s(ldap, NULL, NULL);

    return 0;
}