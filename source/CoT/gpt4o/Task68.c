#include <stdio.h>
#include <ldap.h>

char* searchLDAP(const char *dc, const char *username) {
    LDAP *ld;
    LDAPMessage *result, *entry;
    BerElement *ber;
    char *attribute;
    char *user_info = NULL;
    char search_filter[256];
    snprintf(search_filter, sizeof(search_filter), "(&(dc=%s)(uid=%s))", dc, username);
    int ldap_version = LDAP_VERSION3;

    ldap_initialize(&ld, "ldap://localhost");
    ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &ldap_version);

    if (ldap_search_ext_s(ld, "", LDAP_SCOPE_SUBTREE, search_filter, NULL, 0, NULL, NULL, NULL, 0, &result) == LDAP_SUCCESS) {
        if ((entry = ldap_first_entry(ld, result)) != NULL) {
            if ((attribute = ldap_first_attribute(ld, entry, &ber)) != NULL) {
                user_info = ldap_get_dn(ld, entry);
                ldap_memfree(attribute);
                ber_free(ber, 0);
                ldap_msgfree(result);
                ldap_unbind_ext_s(ld, NULL, NULL);
                return user_info;
            }
        }
        ldap_msgfree(result);
    }

    ldap_unbind_ext_s(ld, NULL, NULL);
    return "";
}

int main() {
    printf("%s\n", searchLDAP("example", "user1"));
    printf("%s\n", searchLDAP("example", "user2"));
    printf("%s\n", searchLDAP("example", "user3"));
    printf("%s\n", searchLDAP("example", "user4"));
    printf("%s\n", searchLDAP("example", "user5"));
    return 0;
}