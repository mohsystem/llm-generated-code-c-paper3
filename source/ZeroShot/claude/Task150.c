
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insert(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if(*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* current = *head;
    while(current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

bool delete(struct Node** head, int data) {
    if(*head == NULL) return false;
    
    if((*head)->data == data) {
        struct Node* temp = *head;
        *head = (*head)->next;
        free(temp);
        return true;
    }
    
    struct Node* current = *head;
    while(current->next != NULL) {
        if(current->next->data == data) {
            struct Node* temp = current->next;
            current->next = current->next->next;
            free(temp);
            return true;
        }
        current = current->next;
    }
    return false;
}

bool search(struct Node* head, int data) {
    struct Node* current = head;
    while(current != NULL) {
        if(current->data == data) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void freeList(struct Node** head) {
    struct Node* current = *head;
    while(current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
}

int main() {
    struct Node* head = NULL;
    
    // Test case 1: Insert elements
    insert(&head, 10);
    insert(&head, 20);
    insert(&head, 30);
    printf("Search 20: %d\\n", search(head, 20)); // Should print 1
    
    // Test case 2: Search non-existent element
    printf("Search 40: %d\\n", search(head, 40)); // Should print 0
    
    // Test case 3: Delete existing element
    printf("Delete 20: %d\\n", delete(&head, 20)); // Should print 1
    
    // Test case 4: Delete non-existent element
    printf("Delete 40: %d\\n", delete(&head, 40)); // Should print 0
    
    // Test case 5: Search after deletion
    printf("Search 20 after deletion: %d\\n", search(head, 20)); // Should print 0
    
    // Free allocated memory
    freeList(&head);
    
    return 0;
}
