#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Mock JNDI context for demonstration (using a simple linked list)

typedef struct JNDINode {
    char *name;
    char *value;
    struct JNDINode *next;
} JNDINode;

JNDINode *jndiContext = NULL;


char* jndiLookup(const char *jndiName) {

    JNDINode *current = jndiContext;
    while (current != NULL) {
        if (strcmp(current->name, jndiName) == 0) {
            return current->value;
        }
        current = current->next;
    }
    char *error_message = malloc(sizeof(char) * (strlen(jndiName) + 30)); // Allocate memory for the error message
    if (error_message == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }
    sprintf(error_message, "Error: JNDI name '%s' not found.", jndiName);
    return error_message;
}


int main() {
    // Initialize mock JNDI context
    JNDINode *node1 = malloc(sizeof(JNDINode));
    node1->name = "java:comp/env/jdbc/myDataSource";
    node1->value = "MockDataSource";
    node1->next = NULL;
    jndiContext = node1;


    JNDINode *node2 = malloc(sizeof(JNDINode));
    node2->name = "java:comp/env/mail/Session";
    node2->value = "MockMailSession";
    node2->next = NULL;
    node1->next = node2;

    // ... (add more nodes as needed)

    printf("%s\n", jndiLookup("java:comp/env/jdbc/myDataSource"));
    printf("%s\n", jndiLookup("java:comp/env/mail/Session"));
    // ... (more lookups)
     printf("%s\n", jndiLookup("java:comp/env/unknownResource"));

    // Free allocated memory (important to avoid memory leaks)
    JNDINode *current = jndiContext;
    while (current != NULL) {
        JNDINode *next = current->next;
        free(current);
        current = next;
    }

    return 0;
}