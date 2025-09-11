#include <stdio.h>
#include <ldap.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <domain> <username>\n", argv[0]);
        return 1;
    }
    char *domain = argv[1];
    char *username = argv[2];
    char ldap_query[256];
    sprintf(ldap_query, "uid=%s,dc=%s", username, domain);
    LDAP *ld;
    ldap_initialize(&ld, "ldap://localhost");
    ldap_simple_bind_s(ld, "cn=Directory Manager", "");
    LDAPMessage *result;
    ldap_search_s(ld, ldap_query, LDAP_SCOPE_SUBTREE, "(objectclass=*)", NULL, 0, &result);
    LDAPMessage *entry = ldap_first_entry(ld, result);
    char *attr;
    for(attr = ldap_first_attribute(ld, entry, &ber); attr != NULL; attr = ldap_next_attribute(ld, entry, ber)) {
        struct berval **vals = ldap_get_values_len(ld, entry, attr);
        printf("%s: %s\n", attr, vals[0]->bv_val);
        ldap_value_free_len(vals);
    }
    ldap_unbind_ext_s(ld, NULL, NULL);
    return 0;
}