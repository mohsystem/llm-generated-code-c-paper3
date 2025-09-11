
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
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

void delete(struct Node** head, int data) {
    if (*head == NULL) return;
    
    if ((*head)->data == data) {
        struct Node* temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }
    
    struct Node* current = *head;
    while (current->next != NULL && current->next->data != data) {
        current = current->next;
    }
    
    if (current->next != NULL) {
        struct Node* temp = current->next;
        current->next = current->next->next;
        free(temp);
    }
}

bool search(struct Node* head, int data) {
    struct Node* current = head;
    while (current != NULL) {
        if (current->data == data) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void freeList(struct Node** head) {
    struct Node* current = *head;
    struct Node* next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

int main() {
    struct Node* head = NULL;
    
    // Test case 1: Insert elements
    insert(&head, 10);
    insert(&head, 20);
    insert(&head, 30);
    printf("Search 20: %d\\n", search(head, 20));  // 1
    
    // Test case 2: Delete middle element
    delete(&head, 20);
    printf("Search 20 after deletion: %d\\n", search(head, 20));  // 0
    
    // Test case 3: Delete first element
    delete(&head, 10);
    printf("Search 10 after deletion: %d\\n", search(head, 10));  // 0
    
    // Test case 4: Search non-existent element
    printf("Search 40: %d\\n", search(head, 40));  // 0
    
    // Test case 5: Insert after deletion
    insert(&head, 50);
    printf("Search 50: %d\\n", search(head, 50));  // 1
    
    // Free the memory
    freeList(&head);
    
    return 0;
}
