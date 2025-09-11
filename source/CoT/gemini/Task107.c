#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock JNDI context for demonstration (replace with actual JNDI implementation)
typedef struct {
    char *key;
    char *value;
} JNDI_Entry;

JNDI_Entry jndi_context[] = {
    {"java:comp/env/jdbc/myDataSource", "jdbc:mysql://localhost/mydb"},
    {"java:comp/env/mail/Session", "mail/Session"},
    {NULL, NULL} // End of entries marker
};


char* jndiLookup(const char* jndiName) {
    int i = 0;

    while(jndi_context[i].key != NULL)
    {
        if(strcmp(jndiName, jndi_context[i].key) == 0)
        {
            return jndi_context[i].value;
        }

        i++;
    }

    fprintf(stderr, "Error: JNDI resource not found: %s\n", jndiName);
    return NULL;
}

int main() {
    printf("%s\n", jndiLookup("java:comp/env/jdbc/myDataSource"));
    printf("%s\n", jndiLookup("java:comp/env/mail/Session"));
    printf("%s\n", jndiLookup("java:comp/env/ejb/MyEJB")); // Will print (null) as not found
    printf("%s\n", jndiLookup("java:comp/env/config/MyConfig")); // Will print (null) as not found
    printf("%s\n", jndiLookup("java:comp/env/queue/MyQueue")); // Will print (null) as not found
    return 0;
}