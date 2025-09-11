// Requires OpenLDAP library
#include <stdio.h>
#include <string.h>
#include <ldap.h>

char* ldapSearch(char *username, char *dc) {
    char *ldap_url = "ldap://localhost:389";
    char base_dn[256];
    char search_filter[256];
    char *result = NULL; // Initialize result to NULL


    snprintf(base_dn, sizeof(base_dn), "dc=%s", dc);
    char *token = strtok(base_dn, ".");
    while (token != NULL) {
        strcat(base_dn, ",dc=");
        strcat(base_dn, token);
        token = strtok(NULL, ".");
    }


    snprintf(search_filter, sizeof(search_filter), "(&(objectClass=user)(sAMAccountName=%s))", username);

    LDAP *ld;
    LDAPMessage *res;
    int rc;

    if ((rc = ldap_initialize(&ld, ldap_url)) != LDAP_SUCCESS) {
        fprintf(stderr, "ldap_initialize: %s\n", ldap_err2string(rc));
        return NULL; // Return NULL on error
    }

    // ... (rest of the LDAP operations - binding, searching, etc.)
      if ((rc = ldap_simple_bind_s(ld, NULL, NULL)) != LDAP_SUCCESS) {
           fprintf(stderr, "ldap_simple_bind_s: %s\n", ldap_err2string(rc));
          ldap_unbind_ext_s(ld, NULL, NULL);
          return NULL;
      }

       if ((rc = ldap_search_ext_s(ld, base_dn, LDAP_SCOPE_SUBTREE, search_filter, NULL, 0, NULL, NULL, NULL, 0, &res)) != LDAP_SUCCESS) {
        fprintf(stderr, "ldap_search_ext_s: %s\n", ldap_err2string(rc));
        ldap_unbind_ext_s(ld, NULL, NULL);
        return NULL;
    }


      // Process results and build the result string
     // ...

    ldap_msgfree(res);
    ldap_unbind_ext_s(ld, NULL, NULL);

    return result; 
}

int main() {

  // Example usage
  printf("%s\n", ldapSearch("user1", "example.com"));
  printf("%s\n", ldapSearch("user2", "test.local"));
  printf("%s\n", ldapSearch("admin", "example.com"));
  printf("%s\n", ldapSearch("guest", "test.local"));
  printf("%s\n", ldapSearch("user3", "example.net"));

    return 0;
}