#include <stdio.h>
#include <ldap.h>

char* searchLDAP(const char* domainComponent, const char* username) {
    LDAP* ld;
    const char* ldapURL = "ldap://localhost:389";
    char baseDN[256];
    char filter[256];
    snprintf(baseDN, sizeof(baseDN), "dc=%s", domainComponent);
    snprintf(filter, sizeof(filter), "(&(objectClass=person)(uid=%s))", username);

    if (ldap_initialize(&ld, ldapURL) != LDAP_SUCCESS) {
        return NULL;
    }

    if (ldap_simple_bind_s(ld, NULL, NULL) != LDAP_SUCCESS) {
        ldap_unbind_ext_s(ld, NULL, NULL);
        return NULL;
    }

    LDAPMessage* result;
    if (ldap_search_ext_s(ld, baseDN, LDAP_SCOPE_SUBTREE, filter, NULL, 0, NULL, NULL, NULL, 0, &result) != LDAP_SUCCESS) {
        ldap_unbind_ext_s(ld, NULL, NULL);
        return NULL;
    }

    LDAPMessage* entry = ldap_first_entry(ld, result);
    if (entry) {
        char* dn = ldap_get_dn(ld, entry);
        ldap_memfree(dn);
        ldap_msgfree(result);
        ldap_unbind_ext_s(ld, NULL, NULL);
        return dn;
    }

    ldap_msgfree(result);
    ldap_unbind_ext_s(ld, NULL, NULL);
    return NULL;
}

int main() {
    printf("%s\n", searchLDAP("example", "user1"));
    printf("%s\n", searchLDAP("example", "user2"));
    printf("%s\n", searchLDAP("example", "user3"));
    printf("%s\n", searchLDAP("example", "user4"));
    printf("%s\n", searchLDAP("example", "user5"));
    return 0;
}