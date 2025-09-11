
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
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

void delete(struct Node** head, int key) {
    struct Node *temp = *head, *prev = NULL;
    
    if (temp != NULL && temp->data == key) {
        *head = temp->next;
        free(temp);
        return;
    }
    
    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }
    
    if (temp == NULL) return;
    
    prev->next = temp->next;
    free(temp);
}

bool search(struct Node* head, int key) {
    struct Node* current = head;
    while (current != NULL) {
        if (current->data == key)
            return true;
        current = current->next;
    }
    return false;
}

int main() {
    struct Node* head = NULL;
    
    // Test Case 1: Insert elements
    insert(&head, 1);
    insert(&head, 2);
    insert(&head, 3);
    
    // Test Case 2: Search existing element
    printf("Search 2: %d\\n", search(head, 2));
    
    // Test Case 3: Search non-existing element
    printf("Search 4: %d\\n", search(head, 4));
    
    // Test Case 4: Delete element
    delete(&head, 2);
    printf("Search after delete 2: %d\\n", search(head, 2));
    
    // Test Case 5: Insert after delete
    insert(&head, 4);
    printf("Search 4 after insert: %d\\n", search(head, 4));
    
    return 0;
}
